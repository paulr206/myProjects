// TODO: Your code to load and parse the JSON file asynchronously.

var button = document.getElementById("btn");


button.addEventListener("click", function(){
    fetch('albums.json')
        .then(response => response.json())
        .then(data => {
            var div = document.getElementById("tableContainer");

            let table = document.createElement("table");
            let thead = document.createElement("thead");
            let tbody = document.createElement("tbody");

            table.appendChild(thead);
            table.appendChild(tbody);

            let inhalt = ["id", "artist", "title", "comment"];
            let headerRow = document.createElement("tr");
            for(var i = 0; i<inhalt.length; i++){
                var zelle = document.createElement("th")
                zelle.textContent = inhalt[i]; 
                headerRow.appendChild(zelle);
            }
            thead.appendChild(headerRow);

            for(var j = 0; j < data.length; j++) {
                console.log("Spalte "+(j+1))
                var bodyRow = document.createElement("tr");
                for(var k = 0; k < inhalt.length; k++) {
                    var zelle2 = document.createElement("td");
                    zelle2.textContent = data[j][inhalt[k]];
                    bodyRow.appendChild(zelle2);
                    console.log(data[j][inhalt[k]]);
                }
                tbody.appendChild(bodyRow);
            }
            
            div.appendChild(table);
        });
});



