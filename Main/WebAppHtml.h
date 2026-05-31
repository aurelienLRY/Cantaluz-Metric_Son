#pragma once
// Cantaluz — app legere (Flash / Standard)

static const char APP_HTML[] PROGMEM = R"CLAPP(
<!DOCTYPE html>
<html lang="fr">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1,viewport-fit=cover">
<meta name="theme-color" content="#1a1030">
<title>Cantaluz</title>
<style>
:root{--bg1:#1a1030;--bg2:#0d1528;--card:rgba(255,255,255,.07);--text:#f0f4ff;--muted:#9ca8c4;--v:#a855f7;--c:#22d3ee;--p:#ec4899;--g:linear-gradient(90deg,var(--v),var(--c),var(--p))}
*{box-sizing:border-box;margin:0;padding:0}
body{font-family:system-ui,sans-serif;background:linear-gradient(165deg,var(--bg1),var(--bg2));color:var(--text);min-height:100vh;padding-bottom:72px}
.grad-t{background:var(--g);-webkit-background-clip:text;-webkit-text-fill-color:transparent;background-clip:text}
.hdr{text-align:center;padding:18px 16px 10px}
.hdr h1{font-size:1.75rem;font-weight:800;background:var(--g);-webkit-background-clip:text;-webkit-text-fill-color:transparent;background-clip:text}
.hdr p{font-size:.86rem;color:var(--muted);margin:8px auto 0;max-width:280px;line-height:1.5}
.wrap{max-width:440px;margin:0 auto;padding:0 14px 14px}
.tab{display:none}.tab.on{display:block}
.card{background:var(--card);border:1px solid rgba(255,255,255,.08);border-radius:16px;padding:14px;margin-bottom:12px}
.card.fb-on{border-color:rgba(34,211,238,.5);box-shadow:0 0 20px rgba(168,85,247,.3)}
.card-t{font-size:.7rem;text-transform:uppercase;letter-spacing:.12em;color:var(--muted);margin-bottom:10px;font-weight:600}
.graph-wrap{height:120px;background:rgba(0,0,0,.25);border-radius:12px;overflow:hidden;margin-bottom:8px}
#graph{width:100%;height:100%;display:block}
.g-legend{display:flex;justify-content:space-between;font-size:.72rem;color:var(--muted)}
.vu{height:10px;background:rgba(0,0,0,.35);border-radius:99px;margin-top:10px;overflow:hidden}
.vu-f{height:100%;width:4%;background:var(--g);border-radius:99px;transition:width .4s}
.modes{display:flex;flex-direction:column;gap:8px}
.mode-btn{border:2px solid rgba(255,255,255,.1);background:rgba(0,0,0,.2);border-radius:14px;padding:14px 12px;text-align:left;cursor:pointer;width:100%}
.mode-btn.on{border-color:var(--v);background:rgba(168,85,247,.2);box-shadow:0 0 16px rgba(168,85,247,.35)}
.mode-btn b{display:block;font-size:1.05rem;margin-bottom:4px;font-weight:800}
.mode-btn span{font-size:.78rem;color:var(--muted);line-height:1.35}
.field{margin-bottom:14px}
.fh{display:flex;align-items:center;gap:6px;margin-bottom:5px}
.fh label{flex:1;font-weight:600;font-size:.9rem}
.fv{color:var(--c);font-weight:700;font-size:.85rem}
.btn-rst,.tip{width:28px;height:28px;border-radius:50%;border:0;font-size:.7rem;font-weight:700;cursor:pointer}
.btn-rst{background:rgba(236,72,153,.15);color:var(--p)}
.tip{background:rgba(34,211,238,.12);color:var(--c)}
.tip.on{background:var(--c);color:#0d1528}
.bub{display:none;font-size:.78rem;color:var(--muted);padding:8px 10px;margin-bottom:6px;border-left:3px solid var(--c);background:rgba(34,211,238,.06);line-height:1.4}
.bub.show{display:block}
input[type=range]{width:100%;height:6px;-webkit-appearance:none;background:rgba(255,255,255,.12);border-radius:99px}
input[type=range]::-webkit-slider-thumb{-webkit-appearance:none;width:20px;height:20px;border-radius:50%;background:var(--g)}
.nav{position:fixed;bottom:0;left:0;right:0;display:flex;background:#0d1528f0;border-top:1px solid rgba(168,85,247,.25);padding:6px 8px calc(6px + env(safe-area-inset-bottom));z-index:50}
.nav button{flex:1;border:0;background:0;color:var(--muted);padding:10px 4px;font-size:.75rem;font-weight:600;border-radius:10px;cursor:pointer}
.nav button.on{color:var(--text);background:rgba(168,85,247,.25)}
.btn-save{width:100%;padding:14px;border:0;border-radius:12px;background:var(--g);color:#fff;font-size:.95rem;font-weight:700;margin-top:6px;cursor:pointer}
.toast{position:fixed;top:72px;left:50%;transform:translateX(-50%) translateY(-50px);background:#121a28f5;border:1px solid rgba(34,211,238,.45);color:#fff;padding:10px 18px;border-radius:14px;font-size:.85rem;font-weight:600;opacity:0;transition:.3s;z-index:60;pointer-events:none;white-space:nowrap}
.toast.show{transform:translateX(-50%) translateY(0);opacity:1}
</style>
</head>
<body>
<header class="hdr">
<h1>Cantaluz</h1>
<p>Outil d'accompagnement au calme.</p>
</header>
<div id="toast" class="toast"></div>
<main class="wrap">
<section id="tab-dash" class="tab on">
<div class="card" id="card-graph">
<div class="card-t">Ambiance sonore</div>
<div class="graph-wrap"><canvas id="graph"></canvas></div>
<div class="g-legend"><span>30 s</span><span>Maintenant</span></div>
<div class="vu"><div class="vu-f" id="vu"></div></div>
</div>
<div class="card" id="card-mode">
<div class="card-t">Mode</div>
<div class="modes">
<button type="button" class="mode-btn" id="m0" data-mode="0"><b class="grad-t">Flash</b><span>Les pics sonores sont signalés par des flashs bleus.</span></button>
<button type="button" class="mode-btn" id="m1" data-mode="1"><b class="grad-t">Standard</b><span>Un vu-mètre qui oscille au gré de l'ambiance captée.</span></button>
</div>
</div>
</section>
<section id="tab-reg" class="tab">
<div class="card" id="card-reg">
<div class="card-t">Paramètres</div>
<div class="field" data-f="vert">
<div class="fh"><label>Zone calme</label><span class="fv" id="vv">400</span><button type="button" class="btn-rst" data-field="vert">&#8634;</button><button type="button" class="tip" data-tip="tip-v">i</button></div>
<p class="bub" id="tip-v">Classe discrète : ruban surtout vert.</p>
<input type="range" id="vert" min="50" max="900" step="10">
</div>
<div class="field" data-f="orange">
<div class="fh"><label>Zone animée</label><span class="fv" id="vo">700</span><button type="button" class="btn-rst" data-field="orange">&#8634;</button><button type="button" class="tip" data-tip="tip-o">i</button></div>
<p class="bub" id="tip-o">Plus de bruit : passage à l'orange.</p>
<input type="range" id="orange" min="100" max="1020" step="10">
</div>
<div class="field" data-f="bright">
<div class="fh"><label>Luminosité</label><span class="fv" id="vb">80</span><button type="button" class="btn-rst" data-field="bright">&#8634;</button><button type="button" class="tip" data-tip="tip-l">i</button></div>
<p class="bub" id="tip-l">Luminosité globale du ruban.</p>
<input type="range" id="bright" min="5" max="255" step="5">
</div>
<div class="field" data-f="attack">
<div class="fh"><label>Montée de la barre</label><span class="fv" id="va">45%</span><button type="button" class="btn-rst" data-field="attack">&#8634;</button><button type="button" class="tip" data-tip="tip-a">i</button></div>
<p class="bub" id="tip-a">Vitesse de la barre lumineuse.</p>
<input type="range" id="attack" min="5" max="100" step="5">
</div>
<button type="button" class="btn-save" id="save">Enregistrer</button>
</div>
</section>
</main>
<nav class="nav">
<button type="button" class="on" data-tab="tab-dash">Dashboard</button>
<button type="button" data-tab="tab-reg">Réglages</button>
</nav>
<script>
var mode=0,hist=[],G,edit=0,applyT=0,lastF='',dashOn=1,tick=0;
function qs(id){return document.getElementById(id)}
function toast(m){qs('toast').textContent=m;qs('toast').classList.add('show');setTimeout(function(){qs('toast').classList.remove('show')},2000)}
function vibe(){try{navigator.vibrate&&navigator.vibrate(30)}catch(e){}}
function fb(msg,k){toast(msg);vibe();var c=k==='mode'?qs('card-mode'):qs('card-reg');c.classList.add('fb-on');setTimeout(function(){c.classList.remove('fb-on')},500)}
function syncMode(m){mode=+m;qs('m0').className='mode-btn'+(mode===0?' on':'');qs('m1').className='mode-btn'+(mode===1?' on':'')}
function syncSl(j){qs('vert').value=j.vert;qs('orange').value=j.orange;qs('bright').value=j.brightness;qs('attack').value=j.attack;qs('vv').textContent=j.vert;qs('vo').textContent=j.orange;qs('vb').textContent=j.brightness;qs('va').textContent=j.attack+'%'}
function par(){return'vert='+qs('vert').value+'&orange='+qs('orange').value+'&bright='+qs('bright').value+'&attack='+qs('attack').value+'&mode='+mode}
async function applyNow(k){try{var r=await fetch('/api/settings?'+par());var j=await r.json();if(!j.ok)return toast('Échec');syncSl(j);syncMode(j.mode);fb(k==='mode'?(j.mode?'Mode Standard activé':'Mode Flash activé'):'Réglage enregistré',k);edit=0}catch(e){toast('Erreur réseau')}}
function sched(id){lastF=id;edit=1;clearTimeout(applyT);applyT=setTimeout(function(){applyNow('reg')},550)}
function drawG(){if(!G||hist.length<2)return;var x=G,c=x.getContext('2d'),w=x.width,h=x.height,n=hist.length,i,d;x.width=x.width;c.clearRect(0,0,w,h);c.strokeStyle='#22d3ee';c.lineWidth=2;c.beginPath();for(i=0;i<n;i++){var px=2+i*(w-4)/(n-1),py=h-3-(hist[i]/100)*(h-6);if(!i)c.moveTo(px,py);else c.lineTo(px,py)}c.stroke()}
function resizeG(){G=qs('graph');if(!G)return;G.width=G.offsetWidth;G.height=G.offsetHeight;drawG()}
document.querySelectorAll('.nav button').forEach(function(b){b.onclick=function(){document.querySelectorAll('.nav button').forEach(function(x){x.classList.remove('on')});document.querySelectorAll('.tab').forEach(function(x){x.classList.remove('on')});b.classList.add('on');qs(b.getAttribute('data-tab')).classList.add('on');dashOn=b.getAttribute('data-tab')==='tab-dash';if(dashOn)setTimeout(resizeG,50)}});
document.querySelectorAll('.tip').forEach(function(b){b.onclick=function(){qs(b.getAttribute('data-tip')).classList.toggle('show');b.classList.toggle('on')}});
['vert','orange','bright','attack'].forEach(function(id){var e=qs(id);e.oninput=function(){var t=qs('v'+id[0]);if(t)t.textContent=id==='attack'?e.value+'%':e.value;sched(id)}});
document.querySelectorAll('.mode-btn').forEach(function(b){b.onclick=function(){syncMode(b.getAttribute('data-mode'));applyNow('mode')}});
document.querySelectorAll('.btn-rst').forEach(function(b){b.onclick=async function(){try{var r=await fetch('/api/reset?field='+b.getAttribute('data-field'));var j=await r.json();if(j.ok){syncSl(j);fb('Valeur d\'origine','reg')}}catch(e){}}});
async function poll(){if(!dashOn){tick++;return}try{var r=await fetch('/api/status');var j=await r.json();var n=j.niveau!=null?j.niveau:j.barre;qs('vu').style.width=Math.max(4,n)+'%';if(!hist.length||hist[hist.length-1]!=n){hist.push(n);if(hist.length>28)hist.shift();drawG()}if(!edit){syncSl(j);syncMode(j.mode)}}catch(e){}tick++}
qs('save').onclick=function(){applyNow('reg')};
setTimeout(function(){resizeG();poll();setInterval(poll,900)},400);
</script>
</body>
</html>
)CLAPP";
