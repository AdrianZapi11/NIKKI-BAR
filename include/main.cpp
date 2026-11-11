#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
#include <SD.h>
#include "index.h"

// ===============================
// WIFI
// ===============================
const char* ssid = "NIKKI BAR";
const char* password = "NIKKI1234";

AsyncWebServer server(80);

// ===============================
// GPIO DE LAS BOMBAS
// ===============================
#define PUMP_VODKA   5
#define PUMP_GIN     22
#define PUMP_RON     21
#define PUMP_LIMON   19
#define PUMP_NARANJA 18
#define PUMP_TONICA  23

// ===============================
// MICROSD OPCIONAL
// ===============================
#define SD_CS   25
#define SD_MOSI 26
#define SD_MISO 14
#define SD_SCK  27

SPIClass hspi(HSPI);
bool sdDisponible = false;

// ===============================
// CONTROL DE PEDIDOS
// ===============================
portMUX_TYPE pedidoMux = portMUX_INITIALIZER_UNLOCKED;

unsigned long pedidoPendiente[6] = {0, 0, 0, 0, 0, 0};
bool hayPedidoPendiente = false;
bool dispensing = false;

struct Pump {
    uint8_t pin;
    unsigned long duration;
    unsigned long startTime;
    bool active;
};

Pump pumps[6] = {
    {PUMP_VODKA,   0, 0, false},
    {PUMP_GIN,     0, 0, false},
    {PUMP_RON,     0, 0, false},
    {PUMP_LIMON,   0, 0, false},
    {PUMP_NARANJA, 0, 0, false},
    {PUMP_TONICA,  0, 0, false}
};

// ===============================
// LECTURA SEGURA DE PARAMETROS
// ===============================
unsigned long readDuration(
    AsyncWebServerRequest *request,
    const char* name
) {
    if (!request->hasParam(name)) {
        return 0;
    }

    String value = request->getParam(name)->value();

    if (value.length() == 0) {
        return 0;
    }

    for (size_t i = 0; i < value.length(); i++) {
        if (!isDigit(value[i])) {
            return 0;
        }
    }

    return strtoul(value.c_str(), nullptr, 10);
}

// ===============================
// APAGAR TODAS LAS BOMBAS
// ===============================
void resetPumps() {
    for (int i = 0; i < 6; i++) {
        digitalWrite(pumps[i].pin, LOW);
        pumps[i].duration = 0;
        pumps[i].startTime = 0;
        pumps[i].active = false;
    }
}

// ===============================
// ARRANCAR UNA BOMBA
// ===============================
void startPump(int index, unsigned long duration) {
    if (duration == 0) {
        digitalWrite(pumps[index].pin, LOW);
        pumps[index].active = false;
        return;
    }

    pumps[index].duration = duration;
    pumps[index].startTime = millis();
    pumps[index].active = true;

    digitalWrite(pumps[index].pin, HIGH);

    Serial.printf(
        "[ON] Bomba %d, GPIO %d, tiempo %lu ms\n",
        index + 1,
        pumps[index].pin,
        duration
    );
}

// ===============================
// RECIBIR Y ARRANCAR PEDIDO
// ===============================
void processPendingOrder() {
    unsigned long durations[6];
    bool startOrder = false;

    portENTER_CRITICAL(&pedidoMux);

    if (hayPedidoPendiente && !dispensing) {
        for (int i = 0; i < 6; i++) {
            durations[i] = pedidoPendiente[i];
            pedidoPendiente[i] = 0;
        }

        hayPedidoPendiente = false;
        dispensing = true;
        startOrder = true;
    }

    portEXIT_CRITICAL(&pedidoMux);

    if (!startOrder) {
        return;
    }

    Serial.println();
    Serial.println("========== NUEVO PEDIDO ==========");

    resetPumps();

    for (int i = 0; i < 6; i++) {
        startPump(i, durations[i]);
    }
}

// ===============================
// ACTUALIZAR Y APAGAR BOMBAS
// ===============================
void updatePumps() {
    bool anyActive = false;

    for (int i = 0; i < 6; i++) {
        if (!pumps[i].active) {
            continue;
        }

        unsigned long elapsed = millis() - pumps[i].startTime;

        if (elapsed >= pumps[i].duration) {
            digitalWrite(pumps[i].pin, LOW);
            pumps[i].active = false;

            Serial.printf(
                "[OFF] Bomba %d, GPIO %d\n",
                i + 1,
                pumps[i].pin
            );
        } else {
            anyActive = true;
        }
    }

    if (!anyActive) {
        bool wasDispensing;

        portENTER_CRITICAL(&pedidoMux);
        wasDispensing = dispensing;
        dispensing = false;
        portEXIT_CRITICAL(&pedidoMux);

        if (wasDispensing) {
            Serial.println("[OK] Pedido terminado.");
        }
    }
}

// ===============================
// SETUP
// ===============================
void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("==================================");
    Serial.println("       INICIANDO NIKKI BAR");
    Serial.println("==================================");

    // Todas las bombas comienzan apagadas.
    for (int i = 0; i < 6; i++) {
        pinMode(pumps[i].pin, OUTPUT);
        digitalWrite(pumps[i].pin, LOW);
    }

    resetPumps();

    Serial.println("[OK] GPIO configurados.");

    // La SD es opcional.
    Serial.println("[INFO] Inicializando MicroSD...");

    hspi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    sdDisponible = SD.begin(SD_CS, hspi);

    if (sdDisponible) {
        Serial.println("[OK] MicroSD detectada.");
    } else {
        Serial.println("[AVISO] MicroSD no disponible.");
        Serial.println("[INFO] La web seguira funcionando.");
    }

    // Punto de acceso.
    Serial.println("[INFO] Iniciando Wi-Fi...");

    WiFi.mode(WIFI_AP);
    WiFi.setSleep(false);

    bool wifiOK = WiFi.softAP(ssid, password);

    if (!wifiOK) {
        Serial.println("[ERROR] No se pudo iniciar Wi-Fi.");
    } else {
        Serial.println("[OK] Wi-Fi iniciado.");
        Serial.print("[WIFI] Red: ");
        Serial.println(ssid);
        Serial.print("[WIFI] Clave: ");
        Serial.println(password);
        Serial.print("[WIFI] IP: ");
        Serial.println(WiFi.softAPIP());
    }

    // Página original de NIKKI BAR.
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(
            200,
            "text/html; charset=utf-8",
            index_html
        );
    });

    // Recibir pedido desde los botones de la página.
    server.on("/servir", HTTP_GET, [](AsyncWebServerRequest *request) {
        unsigned long durations[6];

        durations[0] = readDuration(request, "v");
        durations[1] = readDuration(request, "g");
        durations[2] = readDuration(request, "r");
        durations[3] = readDuration(request, "l");
        durations[4] = readDuration(request, "n");
        durations[5] = readDuration(request, "t");

        bool validOrder = false;

        for (int i = 0; i < 6; i++) {
            if (durations[i] > 0) {
                validOrder = true;
            }
        }

        if (!validOrder) {
            request->send(
                400,
                "text/plain",
                "Pedido vacio o invalido"
            );
            return;
        }

        bool accepted = false;
        bool busy = false;

        portENTER_CRITICAL(&pedidoMux);

        if (dispensing || hayPedidoPendiente) {
            busy = true;
        } else {
            for (int i = 0; i < 6; i++) {
                pedidoPendiente[i] = durations[i];
            }

            hayPedidoPendiente = true;
            accepted = true;
        }

        portEXIT_CRITICAL(&pedidoMux);

        if (busy) {
            request->send(
                409,
                "text/plain",
                "Ya hay una bebida en preparacion"
            );
            return;
        }

        if (accepted) {
            Serial.println("[INFO] Pedido recibido.");
            request->send(200, "text/plain", "OK");
        }
    });

    // Estado del dispensador.
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        bool currentState;

        portENTER_CRITICAL(&pedidoMux);
        currentState = dispensing || hayPedidoPendiente;
        portEXIT_CRITICAL(&pedidoMux);

        String json = "{\"dispensing\":";
        json += currentState ? "true" : "false";
        json += "}";

        request->send(200, "application/json", json);
    });

    // Servir archivos adicionales desde la SD, si existe.
    server.onNotFound([](AsyncWebServerRequest *request) {
        if (!sdDisponible) {
            request->send(404, "text/plain", "Archivo no disponible");
            return;
        }

        String path = request->url();

        if (!SD.exists(path)) {
            request->send(404, "text/plain", "Archivo no encontrado");
            return;
        }

        String contentType = "application/octet-stream";

        if (path.endsWith(".jpg") || path.endsWith(".jpeg")) {
            contentType = "image/jpeg";
        } else if (path.endsWith(".png")) {
            contentType = "image/png";
        } else if (path.endsWith(".gif")) {
            contentType = "image/gif";
        } else if (path.endsWith(".svg")) {
            contentType = "image/svg+xml";
        } else if (path.endsWith(".css")) {
            contentType = "text/css";
        } else if (path.endsWith(".js")) {
            contentType = "application/javascript";
        }

        request->send(SD, path, contentType);
    });

    server.begin();

    Serial.println("[OK] Servidor web iniciado.");
    Serial.print("[WEB] http://");
    Serial.println(WiFi.softAPIP());
    Serial.println("NIKKI BAR listo.");
}

// ===============================
// LOOP PRINCIPAL
// ===============================
void loop() {
    processPendingOrder();
    updatePumps();
    delay(2);
}
