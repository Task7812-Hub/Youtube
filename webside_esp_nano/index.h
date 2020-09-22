const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>

<div class="counter-text"><div id="counter-value" class="value">HIER_ERSCHEINT_DER_WERT</div></div>


<script>
    var counter_value_ub = 0; //start value
    var periodicCheck; //var for periodic check

    startDataChecks();

    
//===============================================================
//  Function to refresh realativHumidity from esp "data"
//===============================================================
    function getDataFromServer_refresh()
    {
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            
            var myObj = JSON.parse(this.responseText);
            counter_value_ub = parseFloat(myObj.uebergabe);
            updateView();
            }
    };

    xmlhttp.open("GET", "/data");
    xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xmlhttp.send();
    }

//===============================================================
//  update content in output
//===============================================================        
    function updateView(){
       document.getElementById("counter-value").innerHTML = counter_value_ub + " [-]";
    }

   
//===============================================================
//  update interval for webside to get value from esp
//=============================================================== 
    function startDataChecks(){
        periodicCheck = setInterval(getDataFromServer_refresh, 2500);
    }
  

</script>

</body>
</html>
)=====";
