const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>Pomiary</title>
<script>
function getMeasurements() {
nocache = '?nocache='+ Math.random() * 1000000;
var request = new XMLHttpRequest();
request.onreadystatechange = function() {
if (this.readyState == 4) {
if (this.status == 200) {
if (this.responseText != null) {

	var responseArray = this.responseText.split(';');

	var allNode = document.getElementById('val');
	while (allNode.firstChild) {
		allNode.removeChild(allNode.firstChild);
	}

	for(var i = 0; i<responseArray.length -1 ; i=i+2) {
		var d1 = document.createElement('div');  
		d1.setAttribute('class', 'm');
		
		var n1 = document.createElement('div');  
		n1.setAttribute('class', 'mName');
		n1.innerHTML = responseArray[i];
		d1.appendChild(n1);
	
		var v1 = document.createElement('div');  
		v1.setAttribute('class', 'mValue');
		v1.innerHTML = responseArray[i+1];
		d1.appendChild(v1);
	
		allNode.appendChild(d1); 
	}	




}}}}
request.open('GET', '/getMeasurements' + nocache, true);
request.send(null);
setTimeout('getMeasurements()', 2000);
}

</script>
<style>
body {
    background-color: #ffffff;
	color: #538135;
}

h1 {
    text-align: center;
} 

.m {
	width: 180px;
	margin: 10px;
	border: 2px solid #a8d08d;
	float: left;
}

.m .mName {
	padding: 3px;
	font-size: 12px;
}

.m .mValue {
	background-color: #e2efd9;
	text-align: center;
	font-size: 28px;
	padding: 5px;
	font-weight: bold;
}
</style>
</head>
<body onload='getMeasurements()'>
<h1>aitMeteorologyStation - ESP8266</h1>
<div id="val"></div>
</body>
</html>
)=====";