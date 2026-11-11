#ifndef INDEX_H
#define INDEX_H

#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    
    <meta name="mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
    <meta name="theme-color" content="#07070a">

    <title>NIKKI - Advanced Cocktail Bar</title>
    <style>
        :root {
            --bg-dark: #07070a;
            --panel-bg: rgba(20, 20, 35, 0.4);
            --panel-border: rgba(255, 255, 255, 0.06);
            --text-main: #f8fafc;
            --text-muted: #94a3b8;
            --accent-cyan: #00f2fe;
            --gradient-primary: linear-gradient(135deg, #00f2fe 0%, #7928ca 50%, #ff007f 100%);
        }
        * { box-sizing: border-box; margin: 0; padding: 0; -webkit-tap-highlight-color: transparent; }
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            background-color: var(--bg-dark);
            background-image:
                radial-gradient(circle at 10% 20%, rgba(121, 40, 202, 0.12) 0%, transparent 40%),
                radial-gradient(circle at 90% 80%, rgba(0, 242, 254, 0.08) 0%, transparent 50%);
            background-attachment: fixed;
            color: var(--text-main);
            padding: 40px 20px;
            display: flex;
            flex-direction: column;
            align-items: center;
            min-height: 100vh;
            letter-spacing: -0.02em;
        }
        .brand-container { text-align: center; margin-bottom: 40px; }
        .logo-nikki {
            font-size: 3.5rem; font-weight: 900; text-transform: uppercase; letter-spacing: 12px;
            background: var(--gradient-primary); -webkit-background-clip: text; -webkit-text-fill-color: transparent;
            filter: drop-shadow(0 2px 20px rgba(121, 40, 202, 0.3)); margin-bottom: 6px;
        }
        .logo-badge {
            font-size: 0.7rem; text-transform: uppercase; letter-spacing: 4px; color: var(--text-muted);
            border: 1px solid var(--panel-border); padding: 5px 16px; border-radius: 30px;
            background: rgba(255, 255, 255, 0.02); backdrop-filter: blur(5px);
        }
        .grid-tragos {
            display: grid; grid-template-columns: repeat(auto-fit, minmax(320px, 1fr));
            gap: 25px; width: 100%; max-width: 1140px; margin-bottom: 120px;
        }
        .card-trago {
            background: var(--panel-bg); border: 1px solid var(--panel-border); border-radius: 24px;
            padding: 20px; display: flex; gap: 20px; align-items: center; backdrop-filter: blur(20px);
            -webkit-backdrop-filter: blur(20px); transition: all 0.4s cubic-bezier(0.16, 1, 0.3, 1);
            position: relative; overflow: hidden; cursor: pointer;
        }
        .card-trago:hover {
            transform: translateY(-4px); border-color: rgba(0, 242, 254, 0.3);
            background: rgba(25, 25, 45, 0.5); box-shadow: 0 20px 40px rgba(0,0,0,0.5);
        }
        .foto-portada {
            width: 90px; height: 120px; border-radius: 16px;
            background-size: cover; background-position: center; flex-shrink: 0;
            box-shadow: inset 0 0 0 1px rgba(255, 255, 255, 0.05);
            background-color: rgba(0,0,0,0.3);
            transition: opacity 0.3s ease;
        }
        .info-portada { display: flex; flex-direction: column; justify-content: center; width: 100%; position: relative; }
        .info-portada h3 { font-size: 1.25rem; color: #ffffff; font-weight: 700; margin-bottom: 4px; padding-right: 25px; }
        .info-portada .sub { color: var(--text-muted); font-size: 0.85rem; margin-bottom: 12px; }
        .btn-dots {
            position: absolute; right: 0; top: 0; background: transparent; border: none;
            color: var(--text-muted); font-size: 1.4rem; cursor: pointer; padding: 5px;
        }
        .modal-overlay {
            position: fixed; top: 0; left: 0; width: 100%; height: 100%;
            background: rgba(3, 3, 5, 0.85); backdrop-filter: blur(15px); -webkit-backdrop-filter: blur(15px);
            display: flex; align-items: center; justify-content: center; z-index: 1000;
            opacity: 0; pointer-events: none; transition: opacity 0.4s ease; padding: 20px;
        }
        .modal-overlay.active { opacity: 1; pointer-events: auto; }
        .modal-content {
            background: #11111e; border: 1px solid rgba(255, 255, 255, 0.1); border-radius: 32px;
            width: 100%; max-width: 450px; padding: 30px; position: relative;
            transform: scale(0.9) translateY(20px); transition: transform 0.4s cubic-bezier(0.16, 1, 0.3, 1);
            box-shadow: 0 30px 60px rgba(0,0,0,0.8); text-align: center;
        }
        .modal-overlay.active .modal-content { transform: scale(1) translateY(0); }
        .btn-cerrar {
            position: absolute; right: 20px; top: 20px; background: rgba(255,255,255,0.05);
            border: none; color: #ffffff; width: 36px; height: 36px; border-radius: 50%;
            font-size: 1.1rem; cursor: pointer; display: flex; align-items: center; justify-content: center;
        }
        .modal-foto {
            width: 100%; height: 220px; border-radius: 20px; background-size: cover;
            background-position: center; margin-bottom: 24px; box-shadow: 0 10px 25px rgba(0,0,0,0.5);
            background-color: rgba(0,0,0,0.3);
        }
        .modal-titulo { font-size: 1.8rem; font-weight: 800; margin-bottom: 8px; color: #fff; }
        .modal-medidas { color: var(--accent-cyan); font-size: 0.8rem; font-weight: 700; letter-spacing: 2px; text-transform: uppercase; margin-bottom: 16px; }
        .modal-descripcion { color: var(--text-muted); font-size: 0.95rem; line-height: 1.5; margin-bottom: 30px; text-align: left; }
        .btn-servir {
            background: #ffffff; color: #000000; border: none; width: 100%; padding: 16px;
            font-weight: 700; font-size: 0.95rem; border-radius: 16px; text-transform: uppercase;
            letter-spacing: 2px; cursor: pointer; transition: all 0.3s;
        }
        .btn-servir:hover { background: var(--gradient-primary); color: #fff; }

        .progress-bar-container {
            width: 100%; background: rgba(255,255,255,0.1); height: 8px;
            border-radius: 10px; overflow: hidden; margin: 20px 0 10px 0;
        }
        .progress-bar {
            width: 0%; height: 100%; background: var(--gradient-primary);
            transition: width 0.1s linear;
        }
        .timer-text { font-size: 0.9rem; color: var(--accent-cyan); font-weight: 700; letter-spacing: 1px; }

        #status-bar {
            position: fixed; bottom: 35px; background: rgba(10, 10, 15, 0.85); border: 1px solid var(--panel-border);
            padding: 18px 45px; border-radius: 100px; font-weight: 600; font-size: 0.95rem; z-index: 2000;
            backdrop-filter: blur(25px); -webkit-backdrop-filter: blur(25px); color: var(--text-muted);
            box-shadow: 0 20px 50px rgba(0,0,0,0.6); text-transform: uppercase; letter-spacing: 1px;
            display: none;
        }
        @media (max-width: 768px) {
            .logo-nikki { font-size: 2.6rem; }
            .grid-tragos { gap: 15px; }
            #status-bar { width: 85%; text-align: center; bottom: 20px; padding: 15px; }
        }
    </style>
</head>
<body>

    <div class="brand-container">
        <div class="logo-nikki">NIKKI</div>
        <div class="logo-badge">Automated Luxury Bar</div>
    </div>

    <div class="grid-tragos">
        <!-- Parámetros: (Título, Medidas, Descripción, Imagen, Vodka, Gin, Ron, Limón, Naranja, Tónica) -->
        <div class="card-trago" onclick="abrirModal('Vodka Citric', 'Vodka 60ml | Limon 140ml', 'Un clásico urbano. Combina vodka con la acidez intensa y refrescante del jugo de limón natural.', '/vodkacitric.jpg', 42350, 0, 0, 84000, 0, 0)">
            <div class="foto-portada" data-src="/vodkacitric.jpg"></div>
            <div class="info-portada">
                <h3>Vodka Citric</h3>
                <p class="sub">Vodka & Limón</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>

        <div class="card-trago" onclick="abrirModal('Screwdriver Pro', 'Vodka 60ml | Naranja 140ml', 'El legendario Destornillador. Fusiona la potencia del vodka con las notas dulces de la naranja madura.', '/screwdriver.jpg', 42350, 0, 0, 0, 73040, 0)">
            <div class="foto-portada" data-src="/screwdriver.jpg"></div>
            <div class="info-portada">
                <h3>Screwdriver Pro</h3>
                <p class="sub">Vodka & Naranja</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>

        <div class="card-trago" onclick="abrirModal('Vodka Tonic', 'Vodka 60ml | Tonica 140ml', 'Para amantes de los tragos secos. La neutralidad del vodka destaca el amargor botánico de la tónica.', '/vodkatonic.jpg', 42350, 0, 0, 0, 0, 84000)">
            <div class="foto-portada" data-src="/vodkatonic.jpg"></div>
            <div class="info-portada">
                <h3>Vodka Tonic</h3>
                <p class="sub">Vodka & Tónica</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>

        <div class="card-trago" onclick="abrirModal('Gin Lemon Sour', 'Gin 60ml | Limon 140ml', 'Un trago electrizante. Combina la compleja base del gin con el choque cítrico de limón.', '/ginlemonsour.jpg', 0, 32720, 0, 84000, 0, 0)">
            <div class="foto-portada" data-src="/ginlemonsour.jpg"></div>
            <div class="info-portada">
                <h3>Gin Lemon Sour</h3>
                <p class="sub">Gin Botánico & Limón</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>

        <div class="card-trago" onclick="abrirModal('Orange Gin Twist', 'Gin 60ml | Naranja 140ml', 'Elegante y frutal. Las notas del gin se entrelazan con el perfil dulce de la naranja fresca.', '/orangegintwist.jpg', 0, 32720, 0, 0, 73040, 0)">
            <div class="foto-portada" data-src="/orangegintwist.jpg"></div>
            <div class="info-portada">
                <h3>Orange Gin Twist</h3>
                <p class="sub">Gin Botánico & Naranja</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>

        <div class="card-trago" onclick="abrirModal('Perfect Gin Tonic', 'Gin 60ml | Tonica 140ml', 'Disruptivo y moderno. El gin aporta notas botánicas que contrastan con el amargor de la tónica.', '/perfectgintonic~2.jpg', 0, 32720, 0, 0, 0, 84000)">
            <div class="foto-portada" data-src="/perfectgintonic~2.jpg"></div>
            <div class="info-portada">
                <h3>Perfect Gin Tonic</h3>
                <p class="sub">Gin Botánico & Tónica</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>

        <div class="card-trago" onclick="abrirModal('Daiquiri Express', 'Ron 60ml | Limon 140ml', 'Un clásico caribeño. Sutil melaza de ron blanco combinada con jugo de limón fresco.', '/daiquiriexpress~2.jpg', 0, 0, 30000, 84000, 0, 0)">
            <div class="foto-portada" data-src="/daiquiriexpress~2.jpg"></div>
            <div class="info-portada">
                <h3>Daiquiri Express</h3>
                <p class="sub">Ron Blanco & Limón</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>

        <div class="card-trago" onclick="abrirModal('Caribbean Sunset', 'Ron 60ml | Naranja 140ml', 'Un viaje directo al caribe. El dulzor del ron se funde de forma perfecta con jugo de naranja fresco.', '/caribbeansunset.jpg', 0, 0, 30000, 0, 73040, 0)">
            <div class="foto-portada" data-src="/caribbeansunset.jpg"></div>
            <div class="info-portada">
                <h3>Caribbean Sunset</h3>
                <p class="sub">Ron Blanco & Naranja</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>

        <div class="card-trago" onclick="abrirModal('Ron Tonic Split', 'Ron 60ml | Tonica 140ml', 'Una combinación inesperada y refrescante. Las notas dulces del ron balanceadas con tónica.', '/rontonicsplit.jpg', 0, 0, 30000, 0, 0, 84000)">
            <div class="foto-portada" data-src="/rontonicsplit.jpg"></div>
            <div class="info-portada">
                <h3>Ron Tonic Split</h3>
                <p class="sub">Ron Blanco & Tónica</p>
                <button class="btn-dots">•••</button>
            </div>
        </div>
    </div>

    <div id="status-bar">Preparando bebida...</div>

    <!-- Modal Detalle Trago -->
    <div class="modal-overlay" id="modalTrago" onclick="cerrarModal(event)">
        <div class="modal-content">
            <button class="btn-cerrar" onclick="document.getElementById('modalTrago').classList.remove('active')">×</button>
            <div class="modal-foto" id="mFoto"></div>
            <div class="modal-titulo" id="mTitulo"></div>
            <div class="modal-medidas" id="mMedidas"></div>
            <div class="modal-descripcion" id="mDescripcion"></div>
            <button class="btn-servir" id="mBtnServir">Servir Trago</button>
        </div>
    </div>

    <!-- Modal de Bloqueo durante el Servido -->
    <div class="modal-overlay" id="modalServing">
        <div class="modal-content">
            <div class="modal-foto" id="sFoto"></div>
            <div class="modal-titulo" id="sTitulo">PREPARANDO TU TRAGO</div>
            <div class="modal-medidas">Por favor espera a que finalice</div>
            <div class="progress-bar-container">
                <div class="progress-bar" id="pBar"></div>
            </div>
            <div class="timer-text" id="pTimer">0s / 0s</div>
        </div>
    </div>

    <script>
        let tragoActual = null;

        document.addEventListener("DOMContentLoaded", function() {
            const fotos = Array.from(document.querySelectorAll('.foto-portada'));
            
            function cargarSiguienteFoto(index) {
                if (index >= fotos.length) return;
                
                const elemento = fotos[index];
                const url = elemento.getAttribute('data-src');
                const imgTemp = new Image();
                
                imgTemp.onload = imgTemp.onerror = function() {
                    elemento.style.backgroundImage = `url('${url}')`;
                    setTimeout(() => cargarSiguienteFoto(index + 1), 50);
                };
                
                imgTemp.src = url;
            }

            cargarSiguienteFoto(0);
        });

        function abrirModal(titulo, medidas, desc, fotoUrl, v, g, r, l, n, t) {
            document.getElementById('mTitulo').innerText = titulo;
            document.getElementById('mMedidas').innerText = medidas;
            document.getElementById('mDescripcion').innerText = desc;
            document.getElementById('mFoto').style.backgroundImage = `url('${fotoUrl}')`;
            
            // Garantizar la correcta conversión a números enteros
            tragoActual = { 
                titulo, 
                fotoUrl, 
                v: parseInt(v) || 0, 
                g: parseInt(g) || 0, 
                r: parseInt(r) || 0, 
                l: parseInt(l) || 0, 
                n: parseInt(n) || 0, 
                t: parseInt(t) || 0 
            };
            
            document.getElementById('mBtnServir').onclick = function() {
                document.getElementById('modalTrago').classList.remove('active');
                enviarBebida();
            };
            
            document.getElementById('modalTrago').classList.add('active');
        }

        function cerrarModal(e) {
            if(e.target.classList.contains('modal-overlay')) {
                document.getElementById('modalTrago').classList.remove('active');
            }
        }

        function enviarBebida() {
            if(!tragoActual) return;
            
            const url = `/servir?v=${tragoActual.v}&g=${tragoActual.g}&r=${tragoActual.r}&l=${tragoActual.l}&n=${tragoActual.n}&t=${tragoActual.t}`;
            
            fetch(url)
                .then(res => {
                    if(res.ok) {
                        const tiempoMaximoMs = Math.max(
                            tragoActual.v, tragoActual.g, tragoActual.r,
                            tragoActual.l, tragoActual.n, tragoActual.t
                        );
                        
                        iniciarAnimacionServido(tragoActual.titulo, tragoActual.fotoUrl, tiempoMaximoMs);
                    } else {
                        throw new Error("Respuesta no OK del servidor");
                    }
                })
                .catch(() => {
                    const statusBar = document.getElementById('status-bar');
                    statusBar.innerText = "Error de conexión";
                    statusBar.className = "";
                    statusBar.style.display = "block";
                    setTimeout(() => { statusBar.style.display = "none"; }, 4000);
                });
        }

        function iniciarAnimacionServido(nombreTrago, fotoUrl, tiempoTotalMs) {
            const modalServing = document.getElementById('modalServing');
            const sTitulo = document.getElementById('sTitulo');
            const sFoto = document.getElementById('sFoto');
            const pBar = document.getElementById('pBar');
            const pTimer = document.getElementById('pTimer');

            sFoto.style.backgroundImage = `url('${fotoUrl}')`;
            sTitulo.innerText = `PREPARANDO ${nombreTrago.toUpperCase()}`;
            modalServing.classList.add('active');

            const tiempoTotalSeg = (tiempoTotalMs / 1000).toFixed(1);
            let tiempoTranscurridoMs = 0;
            const intervalo = 100;

            const timer = setInterval(() => {
                tiempoTranscurridoMs += intervalo;
                const porcentaje = Math.min((tiempoTranscurridoMs / tiempoTotalMs) * 100, 100);
                const segActuales = (tiempoTranscurridoMs / 1000).toFixed(1);

                pBar.style.width = `${porcentaje}%`;
                pTimer.innerText = `${segActuales}s / ${tiempoTotalSeg}s`;

                if (tiempoTranscurridoMs >= tiempoTotalMs) {
                    clearInterval(timer);
                    sTitulo.innerText = "¡TRAGO LISTO!";
                    setTimeout(() => {
                        modalServing.classList.remove('active');
                        pBar.style.width = '0%';
                    }, 1000);
                }
            }, intervalo);
        }
    </script>
</body>
</html>
)rawliteral";

#endif
