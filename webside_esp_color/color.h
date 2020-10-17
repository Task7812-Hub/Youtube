const char COLOR_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
<style>
body{padding:0;margin:0}svg:not(:root){display:block}.playable-code{background-color:#f4f7f8;border:none;border-left:6px solid #558abb;border-width:medium medium medium 6px;color:#4d4e53;height:100px;width:90%;padding:10px 10px 0}.playable-canvas{border:1px solid #4d4e53;border-radius:2px}.playable-buttons{text-align:right;width:90%;padding:5px 10px 5px 26px}
 </style>       
        <title>&lt;input type=&#34;color&#34;&gt; - Example - code sample</title>
    </head>
    <body>
        
            <p>An example demonstrating the use of the <code>&lt;input type="color"&gt;</code>
   control.</p>

<label for="colorWell">Color:</label>
<form id="myForm" action="#" method="POST">

  <!-- Hier wird der Wert aus dem Color Picker angezeigt -->
  <div><input type="text" id="testwert" name="testwert" ></div>

  <!-- Colorpicker -->
  <div><input type="color" value="#ff0000" id="colorWell" ></div>

  <!-- LED Auswahl -->
  <div><input type="checkbox" class="led1" name="led1" id="led1" checked><label for="led1">Led1</label></div>
  <div><input type="checkbox" class="led2" name="led2" id="led2" checked><label for="led2">Led2</label></div>
  <div><input type="checkbox" class="led3" name="led3" id="led3" checked><label for="led3">Led3</label></div>
  <div><input type="checkbox" class="led4" name="led4" id="led4" checked><label for="led4">Led4</label></div>
  <div><input type="checkbox" class="led5" name="led5" id="led5" checked><label for="led5">Led5</label></div>
  <div><input type="checkbox" class="led6" name="led6" id="led6" checked><label for="led6">Led6</label></div>
  <div><input type="checkbox" class="led7" name="led7" id="led7" checked><label for="led7">Led7</label></div>
  <div><input type="checkbox" class="led8" name="led8" id="led8" checked><label for="led8">Led8</label></div>

  <!-- Helligkeit -->
  <div><input type="range" name="slider" id="slider" min="0" max="255" step="1" value="50" data-orientation="vertical"></div>
</form>


<p>COLOR TEST</p>
             
<script>
var colorWell;
var defaultColor = "#0000ff";

// Startup Funktion aufrufen
window.addEventListener("load", startup, false);

//Startfunktion prueft unter anderem ob sich ein Wert anedert
 function startup() {
  
  //purefen ob sich an der Farbe was aendert
  colorWell = document.querySelector("#colorWell");
  colorWell.value = defaultColor;
  colorWell.addEventListener("input", updateFirst, false);
  colorWell.addEventListener("change", updateAll, false);
  colorWell.select();

  //purefen ob sich am slider was aendert
  slider = document.querySelector("#slider");
  slider.addEventListener("change", updateslider, false);
  
}

//Update die Farbe bevor was anderes passiert
 function updateFirst(event) {
  var p = document.querySelector("p");

  if (p) {
    p.style.color = event.target.value;
  }
} 


// Update Werte auslesen, wenn die Farbe geändert wird
function updateAll(event) {
  document.querySelectorAll("p").forEach(function(p) {
    
    p.style.color = event.target.value;
    //Wert in Inputfeld schreiben
    document.getElementById("testwert").value = event.target.value;

    //Leds auslesen
    var led1 = document.getElementById('led1');
    var led2 = document.getElementById('led2');
    var led3 = document.getElementById('led3');
    var led4 = document.getElementById('led4');
    var led5 = document.getElementById('led5');
    var led6 = document.getElementById('led6');
    var led7 = document.getElementById('led7');
    var led8 = document.getElementById('led8');

    var slider = document.getElementById('slider').value;
    //alert(slider);
    // PostAjax Funktion zum senden der Werte
    postAjax('#', { led_1: led1.checked, led_2: led2.checked,led_3: led3.checked,led_4: led4.checked,led_5: led5.checked,led_6: led6.checked,led_7: led7.checked,led_8: led8.checked, slide: slider, testwert: event.target.value }, function(data){ console.log(data); });
  });
}

//Werte auslesen und senden wenn der Slider verschoben wird
function updateslider(event) {
  document.querySelectorAll("p").forEach(function(p) {
    
    var slider = document.getElementById('slider').value;
    var testwert = document.getElementById("testwert").value;
    
    // PostAjax Funktion zum senden der Werte
    postAjax('#', { led_1: led1.checked, led_2: led2.checked,led_3: led3.checked,led_4: led4.checked,led_5: led5.checked,led_6: led6.checked,led_7: led7.checked,led_8: led8.checked, slide: slider, testwert: testwert }, function(data){ console.log(data); });
  });
}

//PostAjax sendefunktion
function postAjax(url, data, success) {
      var params = typeof data == 'string' ? data : Object.keys(data).map(
              function(k){ return encodeURIComponent(k) + '=' + encodeURIComponent(data[k]) }
          ).join('&');
  
      var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject("Microsoft.XMLHTTP");
      xhr.open('POST', url);
      xhr.onreadystatechange = function() {
          if (xhr.readyState>3 && xhr.status==200) { success(xhr.responseText); }
      };
      xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
      xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
      xhr.send(params);
      return xhr;
  }



            </script>
        
    </body>
</html>
)=====";
