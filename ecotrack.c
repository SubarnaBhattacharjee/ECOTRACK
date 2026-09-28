<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>EcoTrack - Smart Energy Monitoring System</title>
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<style>
@import url('https://fonts.googleapis.com/css2?family=Poppins:wght@400;500;600;700&display=swap');
*{box-sizing:border-box}
body{margin:0;padding:15px;font-family:'Poppins',sans-serif;background:linear-gradient(135deg,#a8e6cf,#dcedc8,#aed581);min-height:100vh;color:#263238}
.container{max-width:1050px;margin:auto}
.header{text-align:center;padding:15px 10px 20px}
.logo{display:flex;align-items:center;justify-content:center;gap:12px}
.logo-icon{width:48px;height:48px;background:linear-gradient(135deg,#2e7d32,#66bb6a);border-radius:13px;display:flex;align-items:center;justify-content:center;font-size:27px;box-shadow:0 5px 12px rgba(46,125,50,0.25)}
.header h1{margin:0;font-size:38px;color:#1b5e20}
.header p{margin:5px 0 0;color:#2e7d32;font-size:14px}
.card{background:rgba(255,255,255,0.96);border-radius:18px;padding:20px;margin:15px 0;box-shadow:0 8px 22px rgba(0,0,0,0.12)}
.card h2,.card h3{color:#2e7d32;margin-top:0}
.cost-box{background:linear-gradient(90deg,#2e7d32,#43a047);color:white;padding:16px;border-radius:13px;text-align:center;font-weight:600;margin-bottom:18px}
.cost-box input{width:80px;padding:7px;margin:0 6px;border:none;border-radius:8px;text-align:center;font-size:16px;font-weight:700}
.input-grid{display:grid;grid-template-columns:1fr 1fr;gap:13px}
.input-box{background:#f1f8e9;border:1px solid #c5e1a5;padding:14px;border-radius:13px}
.appliance-title{font-weight:700;color:#33691e;font-size:17px;margin-bottom:10px}
.input-row{display:flex;gap:8px;align-items:center;flex-wrap:wrap}
.input-row label{font-size:12px;color:#546e7a}
.input-row input{width:75px;padding:7px;border:2px solid #aed581;border-radius:7px;text-align:center;font-weight:600}
.button-row{display:grid;grid-template-columns:1fr 1fr;gap:12px;margin-top:18px}
.btn{width:100%;padding:14px;border:none;border-radius:12px;font-size:16px;font-weight:700;cursor:pointer;transition:0.2s}
.btn:hover{transform:translateY(-2px)}
.calculate{background:linear-gradient(90deg,#2e7d32,#66bb6a);color:white}
.reset{background:#eceff1;color:#37474f}
.result-grid{display:grid;grid-template-columns:repeat(4,1fr);gap:12px}
.result-card{text-align:center;padding:18px 10px;border-radius:15px;color:white}
.result-card h2{color:white;margin:8px 0 2px;font-size:25px}
.c1{background:linear-gradient(135deg,#43a047,#2e7d32)}
.c2{background:linear-gradient(135deg,#fb8c00,#ef6c00)}
.c3{background:linear-gradient(135deg,#0288d1,#01579b)}
.c4{background:linear-gradient(135deg,#8e24aa,#6a1b9a)}
.two-column{display:grid;grid-template-columns:1fr 1fr;gap:15px}
.alert{border-left:6px solid #e53935}
.alert.good{border-left-color:#2e7d32}
.warning{color:#c62828;font-weight:600}
.success{color:#2e7d32;font-weight:600}
.tip-list{padding-left:20px}
.tip-list li{margin:8px 0}
.score-box{text-align:center;padding:15px}
.score-circle{width:120px;height:120px;border-radius:50%;margin:10px auto;display:flex;align-items:center;justify-content:center;background:#e8f5e9;border:10px solid #66bb6a;font-size:28px;font-weight:700;color:#2e7d32}
.energy-table{width:100%;border-collapse:collapse;margin-top:10px}
.energy-table th,.energy-table td{padding:10px;border-bottom:1px solid #ddd;text-align:center}
.energy-table th{background:#e8f5e9;color:#2e7d32}
.footer{text-align:center;padding:20px;color:#33691e;font-size:13px}
@media(max-width:750px){.input-grid,.two-column{grid-template-columns:1fr}.result-grid{grid-template-columns:1fr 1fr}.header h1{font-size:32px}}
@media(max-width:480px){body{padding:8px}.result-grid{grid-template-columns:1fr}.button-row{grid-template-columns:1fr}.input-row input{width:65px}.card{padding:15px}}
</style>
</head>
<body>
<div class="container">
<div class="header">
<div class="logo"><div class="logo-icon">🌿</div><h1>EcoTrack</h1></div>
<p>Smart Energy Monitoring System • Save Energy • Save Money</p>
</div>
<div class="card">
<div class="cost-box">Electricity Cost: ₹ <input type="number" id="cost" value="0" min="0" step="0.01"> / kWh</div>
<h3>⚡ Enter Your Appliance Details</h3>
<div class="input-grid">
<div class="input-box"><div class="appliance-title">❄️ Air Conditioner</div><div class="input-row"><label>Power (W)</label><input id="ac_w" type="number" value="0" min="0"><label>Qty</label><input id="ac_n" type="number" value="0" min="0"><label>Hours</label><input id="ac_h" type="number" value="0" min="0" step="0.1"></div></div>
<div class="input-box"><div class="appliance-title">🌀 Fan</div><div class="input-row"><label>Power (W)</label><input id="fan_w" type="number" value="0" min="0"><label>Qty</label><input id="fan_n" type="number" value="0" min="0"><label>Hours</label><input id="fan_h" type="number" value="0" min="0" step="0.1"></div></div>
<div class="input-box"><div class="appliance-title">💡 Lights</div><div class="input-row"><label>Power (W)</label><input id="light_w" type="number" value="0" min="0"><label>Qty</label><input id="light_n" type="number" value="0" min="0"><label>Hours</label><input id="light_h" type="number" value="0" min="0" step="0.1"></div></div>
<div class="input-box"><div class="appliance-title">💻 Computer / PC</div><div class="input-row"><label>Power (W)</label><input id="pc_w" type="number" value="0" min="0"><label>Qty</label><input id="pc_n" type="number" value="0" min="0"><label>Hours</label><input id="pc_h" type="number" value="0" min="0" step="0.1"></div></div>
</div>
<div class="button-row"><button class="btn calculate" onclick="calculate()">⚡ Calculate My Energy</button><button class="btn reset" onclick="resetData()">↺ Reset</button></div>
</div>
<div class="result-grid">
<div class="result-card c1"><div>Daily Usage</div><h2 id="dailyUsage">0.00 kWh</h2><small>per day</small></div>
<div class="result-card c2"><div>Monthly Bill</div><h2 id="monthlyBill">₹0</h2><small>30 days</small></div>
<div class="result-card c3"><div>CO₂ Emission</div><h2 id="co2">0.00 kg</h2><small>estimated / day</small></div>
<div class="result-card c4"><div>Potential Saving</div><h2 id="saving">₹0</h2><small>per month</small></div>
</div>
<div class="card"><h3>📊 Appliance-wise Energy Consumption</h3><table class="energy-table"><thead><tr><th>Appliance</th><th>Power</th><th>Quantity</th><th>Hours</th><th>Daily kWh</th></tr></thead><tbody id="energyTable"></tbody></table></div>
<div class="card"><h3>📈 Energy Consumption Graph</h3><canvas id="chart"></canvas></div>
<div class="two-column">
<div class="card alert" id="alertCard"><h3>⚠️ Wastage Alert</h3><div id="alert">Enter your appliance details and click Calculate.</div></div>
<div class="card"><h3>🌱 Green Score</h3><div class="score-box"><div class="score-circle"><span id="score">100</span></div><div id="scoreText">Ready for calculation</div></div></div>
</div>
<div class="card"><h3>💰 Money Saving Tips</h3><ul class="tip-list" id="tips"><li>Enter your actual appliance data to receive personalised tips.</li></ul></div>
<div class="card"><h3>🌍 Environmental Impact</h3><p id="environment">Enter your electricity and appliance usage data to calculate your estimated environmental impact.</p></div>
<div class="footer">EcoTrack © 2026 | Smart Energy Monitoring System</div>
</div>
<script>
let chart=null;
function value(id){return parseFloat(document.getElementById(id).value)||0}
function calculate(){
 const cost=value("cost");
 const appliances=[{name:"AC",power:value("ac_w"),qty:value("ac_n"),hours:value("ac_h")},{name:"Fan",power:value("fan_w"),qty:value("fan_n"),hours:value("fan_h")},{name:"Light",power:value("light_w"),qty:value("light_n"),hours:value("light_h")},{name:"PC",power:value("pc_w"),qty:value("pc_n"),hours:value("pc_h")}];
 appliances.forEach(a=>{a.kwh=(a.power*a.qty*a.hours)/1000});
 const total=appliances.reduce((sum,a)=>sum+a.kwh,0);
 const monthlyEnergy=total*30;
 const bill=monthlyEnergy*cost;
 const co2=total*0.7;
 let wastage=0,tips=[],alerts=[];
 if(value("ac_h")>6){wastage+=2.3;alerts.push("AC usage is above 6 hours/day.");tips.push("❄️ Reduce unnecessary AC usage and keep the temperature around 24°C.");}
 if(value("light_h")>8){wastage+=0.5;alerts.push("Light usage is above 8 hours/day.");tips.push("💡 Use natural daylight whenever possible.");}
 if(value("fan_h")>10){wastage+=0.8;alerts.push("Fan usage is above 10 hours/day.");tips.push("🌀 Switch off fans when leaving the room.");}
 if(value("pc_h")>8){wastage+=0.4;alerts.push("PC usage is above 8 hours/day.");tips.push("💻 Turn off the PC instead of leaving it idle.");}
 const saving=wastage*30*cost;
 let score=100-wastage*10;
 score=Math.max(0,Math.min(100,Math.round(score)));
 document.getElementById("dailyUsage").innerText=total.toFixed(2)+" kWh";
 document.getElementById("monthlyBill").innerText="₹"+bill.toFixed(0);
 document.getElementById("co2").innerText=co2.toFixed(2)+" kg";
 document.getElementById("saving").innerText="₹"+saving.toFixed(0);
 let table="";appliances.forEach(a=>{table+=`<tr><td>${a.name}</td><td>${a.power} W</td><td>${a.qty}</td><td>${a.hours}</td><td><b>${a.kwh.toFixed(2)}</b></td></tr>`;});
 table+=`<tr><td colspan="4"><b>Total Daily Consumption</b></td><td><b>${total.toFixed(2)} kWh</b></td></tr>`;
 document.getElementById("energyTable").innerHTML=table;
 const alertBox=document.getElementById("alert");const alertCard=document.getElementById("alertCard");
 if(alerts.length===0){alertCard.classList.add("good");alertBox.innerHTML=`<p class="success">✅ No major energy wastage detected.</p>`;}else{alertCard.classList.remove("good");alertBox.innerHTML=`${alerts.map(a=>`<p class="warning">⚠️ ${a}</p>`).join("")}<p>Estimated avoidable usage: <b>${wastage.toFixed(1)} kWh/day</b></p>`;}
 if(tips.length===0){if(total===0){tips.push("Enter your actual appliance details to get personalised tips.");}else{tips.push("🌱 Your current usage pattern looks efficient. Keep monitoring your consumption.");}}
 document.getElementById("tips").innerHTML=tips.map(t=>`<li>${t}</li>`).join("");
 document.getElementById("score").innerText=score;
 if(total===0){document.getElementById("scoreText").innerText="Enter your data to calculate your score.";}else if(score>=90){document.getElementById("scoreText").innerText="Excellent energy management!";}else if(score>=70){document.getElementById("scoreText").innerText="Good energy management.";}else if(score>=50){document.getElementById("scoreText").innerText="Moderate energy consumption.";}else{document.getElementById("scoreText").innerText="High energy wastage detected.";}
 if(total===0){document.getElementById("environment").innerText="Enter your appliance usage data to calculate your estimated environmental impact.";}else{document.getElementById("environment").innerHTML=`Your estimated daily electricity consumption is <b>${total.toFixed(2)} kWh</b>. This corresponds to approximately <b>${co2.toFixed(2)} kg of CO₂</b> emissions per day, using an estimated factor of 0.7 kg CO₂/kWh.<br><br>Reducing unnecessary electricity usage can lower both your electricity bill and environmental impact.`;}
 createChart(appliances);
}
function createChart(appliances){
 const ctx=document.getElementById("chart").getContext("2d");
 if(chart){chart.destroy();}
 chart=new Chart(ctx,{type:"bar",data:{labels:appliances.map(a=>a.name),datasets:[{label:"Daily Energy Consumption (kWh)",data:appliances.map(a=>a.kwh),backgroundColor:["#2e7d32","#66bb6a","#aed581","#ff7043"],borderRadius:8}]},options:{responsive:true,plugins:{legend:{display:true}},scales:{y:{beginAtZero:true,title:{display:true,text:"Energy (kWh/day)"}}}}});
}
function resetData(){
 document.getElementById("cost").value=0;
 document.getElementById("ac_w").value=0;document.getElementById("ac_n").value=0;document.getElementById("ac_h").value=0;
 document.getElementById("fan_w").value=0;document.getElementById("fan_n").value=0;document.getElementById("fan_h").value=0;
 document.getElementById("light_w").value=0;document.getElementById("light_n").value=0;document.getElementById("light_h").value=0;
 document.getElementById("pc_w").value=0;document.getElementById("pc_n").value=0;document.getElementById("pc_h").value=0;
 calculate();
}
window.onload=function(){calculate();};
</script>
</body>
</html>