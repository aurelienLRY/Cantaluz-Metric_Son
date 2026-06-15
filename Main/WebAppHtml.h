#pragma once
// Cantaluz — app (Flash / Standard / Méditation guidée / Défi Fifou)

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
.med-phase{font-size:1.6rem;font-weight:800;text-align:center;margin:8px 0 4px;background:var(--g);-webkit-background-clip:text;-webkit-text-fill-color:transparent;background-clip:text}
.med-timer{font-size:2rem;font-weight:800;text-align:center;font-variant-numeric:tabular-nums;color:var(--c)}
.med-sub{text-align:center;font-size:.82rem;color:var(--muted);margin:6px 0 12px}
.med-count{font-size:3rem;font-weight:800;text-align:center;color:var(--p);min-height:3.2rem;line-height:1}
.med-dur-h{display:flex;align-items:center;justify-content:space-between;margin-bottom:8px;gap:8px}
.med-dur-l{font-size:.85rem;font-weight:600;color:var(--text)}
.dur-row{display:flex;gap:8px;margin-bottom:10px}
.dur{flex:1;padding:12px 6px;border:2px solid rgba(255,255,255,.12);border-radius:12px;background:rgba(0,0,0,.2);color:var(--muted);font-weight:700;font-size:.85rem;cursor:pointer}
.dur.on{border-color:var(--v);color:var(--text);background:rgba(168,85,247,.2)}
.btn-stop{width:100%;padding:14px;border:0;border-radius:12px;background:rgba(236,72,153,.35);color:#fff;font-size:.95rem;font-weight:700;margin-top:8px;cursor:pointer}
.hide{display:none!important}
.dim{opacity:.35;pointer-events:none}
.clr{display:inline-block;width:11px;height:11px;border-radius:50%;vertical-align:-1px;margin-right:3px;border:1px solid rgba(255,255,255,.25)}
.clr-in{background:#00c8ff}.clr-ho{background:#ffa000}.clr-ex{background:#ff00b4}.clr-em{background:#dcdcff}
.clr-ff{background:#00c8ff}
.bub-med strong{color:var(--text)}
.fifou-leds{font-size:1.4rem;font-weight:800;text-align:center;color:#00c8ff;margin:4px 0}
.fifou-bar{height:12px;background:rgba(0,0,0,.35);border-radius:99px;overflow:hidden;margin:8px 0}
.fifou-bar-f{height:100%;width:8%;background:linear-gradient(90deg,#00c8ff,#22d3ee);border-radius:99px;transition:width .35s}
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
<div class="card hide" id="card-medit">
<div class="card-t">Méditation guidée</div>
<div class="med-phase" id="med-phase">Prêt</div>
<div class="med-count hide" id="med-count"></div>
<div class="med-timer" id="med-timer">00:00</div>
<div class="med-sub" id="med-sub">Choisissez une durée puis appuyez sur Démarrer.</div>
<div class="med-dur-h" id="med-dur-h">
<span class="med-dur-l">Durée de la séance</span>
<button type="button" class="tip" id="tip-med-btn" data-tip="tip-med">i</button>
</div>
<p class="bub bub-med" id="tip-med"></p>
<div class="dur-row" id="dur-row">
<button type="button" class="dur on" data-dur="120">2 min</button>
<button type="button" class="dur" data-dur="300">5 min</button>
<button type="button" class="dur" data-dur="600">10 min</button>
</div>
<button type="button" class="btn-save" id="med-start">Démarrer</button>
<button type="button" class="btn-stop hide" id="med-stop">Arrêter</button>
</div>
<div class="card hide" id="card-fifou">
<div class="card-t">Défi Fifou</div>
<div class="med-phase" id="fifou-phase">Prêt</div>
<div class="med-count hide" id="fifou-count"></div>
<div class="med-timer" id="fifou-timer">00:00</div>
<div class="fifou-leds" id="fifou-leds">0 / 0 LED</div>
<div class="fifou-bar"><div class="fifou-bar-f" id="fifou-bar"></div></div>
<div class="med-sub" id="fifou-sub">Choisissez une durée puis appuyez sur Démarrer.</div>
<div class="med-dur-h" id="fifou-dur-h">
<span class="med-dur-l">Durée du défi</span>
<button type="button" class="tip" id="tip-fifou-btn" data-tip="tip-fifou">i</button>
</div>
<p class="bub bub-med" id="tip-fifou"></p>
<div class="dur-row" id="fifou-dur-row">
<button type="button" class="dur on" data-fifou-dur="120">2 min</button>
<button type="button" class="dur" data-fifou-dur="300">5 min</button>
<button type="button" class="dur" data-fifou-dur="600">10 min</button>
</div>
<button type="button" class="btn-save" id="fifou-start">Démarrer</button>
<button type="button" class="btn-stop hide" id="fifou-stop">Arrêter</button>
</div>
<div class="card" id="card-mode">
<div class="card-t">Mode</div>
<div class="modes">
<button type="button" class="mode-btn" id="m0" data-mode="0"><b class="grad-t">Flash</b><span>Les pics sonores sont signalés par des flashs bleus.</span></button>
<button type="button" class="mode-btn" id="m1" data-mode="1"><b class="grad-t">Standard</b><span>Un vu-mètre qui oscille au gré de l'ambiance captée.</span></button>
<button type="button" class="mode-btn" id="m2" data-mode="2"><b class="grad-t">Méditation guidée</b><span>Respiration guidée : inspire, retiens, expire — une LED après l'autre.</span></button>
<button type="button" class="mode-btn" id="m3" data-mode="3"><b class="grad-t">Défi Fifou</b><span>Jeu du calme : gagnez des LED en restant silencieux, perdez-en si c'est trop bruyant.</span></button>
</div>
</div>
</section>
<section id="tab-reg" class="tab">
<div class="card" id="card-reg">
<div class="card-t">Paramètres</div>
<div class="field" data-f="sens">
<div class="fh"><label>Sensibilité</label><span class="fv" id="vs">8</span><button type="button" class="btn-rst" data-field="sens">&#8634;</button><button type="button" class="tip" data-tip="tip-s">i</button></div>
<p class="bub" id="tip-s">Plus bas = ruban stable au silence. Plus haut = réaction plus forte à la voix.</p>
<input type="range" id="sens" min="0" max="100" step="5">
</div>
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
var mode=0,hist=[],G,edit=0,dashOn=1,medDur=120,fifouDur=120;
var PH={idle:'Prêt',countdown:'Préparez-vous',inspire:'Inspire',hold:'Retiens',expire:'Expire',holdempty:'Bloque l\'air',pause:'',done:'Terminé'};
var FPH={idle:'Prêt',countdown:'Préparez-vous',playing:'En jeu',won:'Victoire !',lost:'Temps écoulé',done:'Terminé'};
var MEDP={120:{lb:'2 minutes',in:4,ho:2,ex:5,em:2,pa:1},300:{lb:'5 minutes',in:5,ho:3,ex:6,em:2,pa:1},600:{lb:'10 minutes',in:6,ho:4,ex:7,em:3,pa:2}};
var FIFP={120:{lb:'2 minutes',calm:'1 min 20'},300:{lb:'5 minutes',calm:'3 min 20'},600:{lb:'10 minutes',calm:'6 min 40'}};
function qs(id){return document.getElementById(id)}
function medReps(d){var p=MEDP[d]||MEDP[120];return Math.floor((d||120)/(p.in+p.ho+p.ex+p.em+p.pa))}
function updateMedTip(){var p=MEDP[medDur]||MEDP[120],n=medReps(medDur),cy=p.in+p.ho+p.ex+p.em+p.pa;qs('tip-med').innerHTML='<strong>Séance '+p.lb+'</strong> — environ <strong>'+n+' respirations</strong> (cycle '+cy+' s).<br>Chaque respiration : <span class="clr clr-in"></span>Inspire '+p.in+' s → <span class="clr clr-ho"></span>Retiens '+p.ho+' s → <span class="clr clr-ex"></span>Expire '+p.ex+' s → <span class="clr clr-em"></span>Bloque l\'air '+p.em+' s, puis pause '+p.pa+' s.<br>Les LED s\'allument <strong>une par une</strong>, toujours dans le même sens sur tout le ruban.'}
function updateFifouTip(){var p=FIFP[fifouDur]||FIFP[120];qs('tip-fifou').innerHTML='<strong>Défi '+p.lb+'</strong> — il faut environ <strong>'+p.calm+' de calme</strong> pour remplir le bandeau (marge d\'erreur incluse).<br>Départ : <strong>20 LED</strong> <span class="clr clr-ff"></span>cyan. <strong>Calme</strong> = gain · <strong>Animé</strong> = statu quo · <strong>Intense</strong> = perte (plus lente).<br>Victoire = feu d\'artifice · Défaite = clignotement rouge.'}
function toast(m){qs('toast').textContent=m;qs('toast').classList.add('show');setTimeout(function(){qs('toast').classList.remove('show')},2000)}
function vibe(){try{navigator.vibrate&&navigator.vibrate(30)}catch(e){}}
function fb(msg,k){toast(msg);vibe();var c=k==='mode'?qs('card-mode'):qs('card-reg');c.classList.add('fb-on');setTimeout(function(){c.classList.remove('fb-on')},500)}
function fmt(s){s=+s||0;var m=Math.floor(s/60),x=s%60;return(m<10?'0':'')+m+':'+(x<10?'0':'')+x}
function syncMode(m){mode=+m;qs('m0').className='mode-btn'+(mode===0?' on':'');qs('m1').className='mode-btn'+(mode===1?' on':'');qs('m2').className='mode-btn'+(mode===2?' on':'');qs('m3').className='mode-btn'+(mode===3?' on':'');var sess=mode===2||mode===3;qs('card-graph').classList.toggle('hide',sess);qs('card-medit').classList.toggle('hide',mode!==2);qs('card-fifou').classList.toggle('hide',mode!==3);qs('tab-reg').classList.toggle('dim',sess)}
function syncSl(j){qs('sens').value=j.sensitivity!=null?j.sensitivity:8;qs('vert').value=j.vert;qs('orange').value=j.orange;qs('bright').value=j.brightness;qs('attack').value=j.attack;qs('vs').textContent=j.sensitivity!=null?j.sensitivity:8;qs('vv').textContent=j.vert;qs('vo').textContent=j.orange;qs('vb').textContent=j.brightness;qs('va').textContent=j.attack+'%'}
function par(){return'sens='+qs('sens').value+'&vert='+qs('vert').value+'&orange='+qs('orange').value+'&bright='+qs('bright').value+'&attack='+qs('attack').value+'&mode='+mode}
function modeLbl(m){return m===3?'Défi Fifou':m===2?'Méditation guidée':m?'Standard':'Flash'}
async function applyNow(k){try{var r=await fetch('/api/settings?'+par());var j=await r.json();if(!j.ok)return toast('Échec');syncSl(j);syncMode(j.mode);if(k==='mode')fb('Mode '+modeLbl(j.mode)+' activé',k);else fb('Réglages enregistrés',k);edit=0}catch(e){toast('Erreur réseau')}}
function drawG(){if(!G||hist.length<2)return;var x=G,c=x.getContext('2d'),w=x.width,h=x.height,n=hist.length,i;x.width=x.width;c.clearRect(0,0,w,h);c.strokeStyle='#22d3ee';c.lineWidth=2;c.beginPath();for(i=0;i<n;i++){var px=2+i*(w-4)/(n-1),py=h-3-(hist[i]/100)*(h-6);if(!i)c.moveTo(px,py);else c.lineTo(px,py)}c.stroke()}
function resizeG(){G=qs('graph');if(!G)return;G.width=G.offsetWidth;G.height=G.offsetHeight;drawG()}
function syncMed(j){if(mode!==2)return;var run=j.medRunning==='true'||j.medRunning===true;var cnt=j.medCounting==='true'||j.medCounting===true;var ph=j.medPhase||'idle';qs('med-phase').textContent=PH[ph]||ph;qs('dur-row').classList.toggle('dim',run||cnt);qs('med-dur-h').classList.toggle('dim',run||cnt);qs('med-start').classList.toggle('hide',run||cnt);qs('med-stop').classList.toggle('hide',!(run||cnt));if(run||cnt)qs('tip-med').classList.remove('show');if(cnt&&j.medCountdown>0){qs('med-count').classList.remove('hide');qs('med-count').textContent=j.medCountdown;qs('med-timer').textContent=fmt(j.medDur||medDur);qs('med-sub').textContent='La séance commence dans…'}else{qs('med-count').classList.add('hide');if(run){qs('med-timer').textContent=fmt(j.medElapsed||0);qs('med-sub').textContent='Reste '+fmt(j.medRemain||0)+' · durée '+fmt(j.medDur||medDur)}else if(ph==='done'){qs('med-timer').textContent=fmt(j.medDur||medDur);qs('med-sub').textContent='Séance terminée. Bravo !'}else{qs('med-timer').textContent='00:00';qs('med-sub').textContent='Choisissez une durée puis appuyez sur Démarrer.'}}}
function syncFifou(j){if(mode!==3)return;var run=j.fifouRunning==='true'||j.fifouRunning===true;var cnt=j.fifouCounting==='true'||j.fifouCounting===true;var ph=j.fifouPhase||'idle';var maxL=+j.fifouLedsMax||1;var lit=+j.fifouLeds||0;qs('fifou-phase').textContent=FPH[ph]||ph;qs('fifou-leds').textContent=lit+' / '+maxL+' LED';qs('fifou-bar').style.width=Math.max(4,(lit/maxL)*100)+'%';qs('fifou-dur-row').classList.toggle('dim',run||cnt);qs('fifou-dur-h').classList.toggle('dim',run||cnt);qs('fifou-start').classList.toggle('hide',run||cnt);qs('fifou-stop').classList.toggle('hide',!(run||cnt));if(run||cnt)qs('tip-fifou').classList.remove('show');if(cnt&&j.fifouCountdown>0){qs('fifou-count').classList.remove('hide');qs('fifou-count').textContent=j.fifouCountdown;qs('fifou-timer').textContent=fmt(j.fifouDur||fifouDur);qs('fifou-sub').textContent='Le défi commence dans…'}else{qs('fifou-count').classList.add('hide');if(run){qs('fifou-timer').textContent=fmt(j.fifouElapsed||0);qs('fifou-sub').textContent='Reste '+fmt(j.fifouRemain||0)+' · objectif : remplir le bandeau'}else if(ph==='won'){qs('fifou-timer').textContent=fmt(j.fifouDur||fifouDur);qs('fifou-sub').textContent='Victoire ! Le bandeau est rempli. Bravo !'}else if(ph==='lost'){qs('fifou-timer').textContent=fmt(j.fifouDur||fifouDur);qs('fifou-sub').textContent='Temps écoulé — le bandeau n\'est pas rempli.'}else if(ph==='done'&&lit>=maxL){qs('fifou-sub').textContent='Victoire ! Le bandeau est rempli. Bravo !'}else if(ph==='done'){qs('fifou-sub').textContent='Temps écoulé — le bandeau n\'est pas rempli.'}else{qs('fifou-timer').textContent='00:00';qs('fifou-sub').textContent='Choisissez une durée puis appuyez sur Démarrer.'}}}
document.querySelectorAll('.nav button').forEach(function(b){b.onclick=function(){document.querySelectorAll('.nav button').forEach(function(x){x.classList.remove('on')});document.querySelectorAll('.tab').forEach(function(x){x.classList.remove('on')});b.classList.add('on');qs(b.getAttribute('data-tab')).classList.add('on');dashOn=b.getAttribute('data-tab')==='tab-dash';if(dashOn)setTimeout(resizeG,50)}});
document.querySelectorAll('.tip').forEach(function(b){b.onclick=function(){if(b.parentElement&&b.parentElement.classList.contains('dim'))return;var id=b.getAttribute('data-tip');qs(id).classList.toggle('show');b.classList.toggle('on')}});
['sens','vert','orange','bright','attack'].forEach(function(id){var e=qs(id);e.oninput=function(){var t=id==='sens'?qs('vs'):qs('v'+id[0]);if(t)t.textContent=id==='attack'?e.value+'%':e.value;edit=1}});
document.querySelectorAll('.mode-btn').forEach(function(b){b.onclick=function(){syncMode(b.getAttribute('data-mode'));applyNow('mode')}});
document.querySelectorAll('.dur').forEach(function(b){b.onclick=function(){if(qs('dur-row').classList.contains('dim'))return;document.querySelectorAll('.dur').forEach(function(x){x.classList.remove('on')});b.classList.add('on');medDur=+b.getAttribute('data-dur');updateMedTip()}});
qs('med-start').onclick=async function(){try{var r=await fetch('/api/meditation/start?dur='+medDur);var j=await r.json();if(j.ok){toast('Démarrage…');vibe()}else toast('Choisissez le mode Méditation')}catch(e){toast('Erreur réseau')}};
qs('med-stop').onclick=async function(){try{await fetch('/api/meditation/stop');toast('Séance arrêtée')}catch(e){}};
document.querySelectorAll('[data-fifou-dur]').forEach(function(b){b.onclick=function(){if(qs('fifou-dur-row').classList.contains('dim'))return;document.querySelectorAll('[data-fifou-dur]').forEach(function(x){x.classList.remove('on')});b.classList.add('on');fifouDur=+b.getAttribute('data-fifou-dur');updateFifouTip()}});
qs('fifou-start').onclick=async function(){try{var r=await fetch('/api/fifou/start?dur='+fifouDur);var j=await r.json();if(j.ok){toast('Démarrage…');vibe()}else toast('Choisissez le mode Défi Fifou')}catch(e){toast('Erreur réseau')}};
qs('fifou-stop').onclick=async function(){try{await fetch('/api/fifou/stop');toast('Défi arrêté')}catch(e){}};
document.querySelectorAll('.btn-rst').forEach(function(b){b.onclick=async function(){try{var r=await fetch('/api/reset?field='+b.getAttribute('data-field'));var j=await r.json();if(j.ok){syncSl(j);fb('Valeur d\'origine','reg')}}catch(e){}}});
async function poll(){try{var r=await fetch('/api/status');var j=await r.json();if(mode!==2&&mode!==3&&dashOn){var n=j.niveau!=null?j.niveau:j.barre;qs('vu').style.width=Math.max(4,n)+'%';if(!hist.length||hist[hist.length-1]!=n){hist.push(n);if(hist.length>28)hist.shift();drawG()}}if(!edit){syncSl(j);syncMode(j.mode)}syncMed(j);syncFifou(j)}catch(e){}}
qs('save').onclick=function(){applyNow('reg')};
setTimeout(function(){updateMedTip();updateFifouTip();resizeG();poll();setInterval(poll,500)},400);
</script>
</body>
</html>
)CLAPP";
