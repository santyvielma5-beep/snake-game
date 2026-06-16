<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<style>
* { box-sizing: border-box; margin: 0; padding: 0; user-select: none; }
body { background: #0f0f1a; color: white; display: flex; justify-content: center; align-items: center; min-height: 100vh; font-family: sans-serif; }
.arcade { background: #2b1055; border: 4px solid #00f0ff; border-radius: 12px; padding: 15px; width: 340px; text-align: center; box-shadow: 0 0 20px #00f0ff; }
h1 { font-size: 20px; color: #00f0ff; margin-bottom: 5px; }
.score { font-size: 16px; color: #ff007f; margin-bottom: 10px; font-weight: bold; }
canvas { background: #050510; border: 3px solid #ff007f; display: block; margin: 0 auto; }
.pad { margin-top: 15px; display: flex; flex-direction: column; align-items: center; gap: 4px; }
.row { display: flex; gap: 4px; }
.btn { width: 45px; height: 45px; background: #121225; border: 2px solid #00f0ff; border-radius: 6px; color: #00f0ff; font-size: 18px; font-weight: bold; cursor: pointer; }
.btn:active { background: #00f0ff; color: #121225; }
</style>
</head>
<body>
<div class="arcade">
<h1>SNAKE ARCADE</h1>
<div class="score">SCORE: <span id="pts">0</span></div>
<canvas id="canv" width="280" height="280"></canvas>
<div class="pad">
<div class="row"><button class="btn" onclick="mov(0,-1)">▲</button></div>
<div class="row">
<button class="btn" onclick="mov(-1,0)">◀</button>
<button class="btn" style="opacity:0.3;cursor:default;">🕹️</button>
<button class="btn" onclick="mov(1,0)">▶</button>
</div>
<div class="row"><button class="btn" onclick="mov(0,1)">▼</button></div>
</div>
</div>
<script>
var cv = document.getElementById("canv");
var cx = cv.getContext("2d");
var sz = 20, cnt = cv.width / sz;
var sn, cm, dx, dy, sc, go, init;
function start() {
sn = [{x:7,y:7},{x:6,y:7},{x:5,y:7}];
dx=0;dy=0;sc=0;go=false;init=false;
document.getElementById("pts").innerText=sc;
food();
}
function food() {
cm = {x:Math.floor(Math.random()*cnt),y:Math.floor(Math.random()*cnt)};
}
function mov(nx,ny) {
if(go){start();return;}
if(nx!==0&&dx!==0)return;
if(ny!==0&&dy!==0)return;
dx=nx;dy=ny;init=true;
}
window.addEventListener("keydown",function(e){
if([37,38,39,40].indexOf(e.keyCode)>-1)e.preventDefault();
if(go){start();return;}
if(e.keyCode===38&&dy===0)mov(0,-1);
if(e.keyCode===40&&dy===0)mov(0,1);
if(e.keyCode===37&&dx===0)mov(-1,0);
if(e.keyCode===39&&dx===0)mov(1,0);
});
function loop() {
if(!go&&init){
var h={x:sn[0].x+dx,y:sn[0].y+dy};
if(h.x<0||h.x>=cnt||h.y<0||h.y>=cnt)go=true;
for(var i=0;i<sn.length;i++){if(sn[i].x===h.x&&sn[i].y===h.y)go=true;}
if(!go){
sn.unshift(h);
if(h.x===cm.x&&h.y===cm.y){sc+=10;document.getElementById("pts").innerText=sc;food();}
else{sn.pop();}
}
}
cx.fillStyle="#050510";cx.fillRect(0,0,cv.width,cv.height);
cx.fillStyle="#ff4d4d";cx.fillRect(cm.x*sz+1,cm.y*sz+1,sz-2,sz-2);
for(var i=0;i<sn.length;i++){
cx.fillStyle=i===0?"#00f0ff":"#39ff14";
cx.fillRect(sn[i].x*sz+1,sn[i].y*sz+1,sz-2,sz-2);
}
if(go){
cx.fillStyle="rgba(0,0,0,0.8)";cx.fillRect(0,0,cv.width,cv.height);
cx.fillStyle="#ff007f";cx.font="bold 20px sans-serif";cx.textAlign="center";
cx.fillText("GAME OVER",cv.width/2,cv.height/2);
}
setTimeout(loop,120);
}
start();loop();
</script>
</body>
</html>
