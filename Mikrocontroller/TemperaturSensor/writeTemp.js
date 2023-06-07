//import time

function createTable(url){
    fetch(url)
        .then(response => response.json())
        .then(data => {
            const table = document.getElementById("tbl");
            let thead = document.createElement("thead");
            let tbody = document.createElement("tbody");

            table.appendChild(thead);
            table.appendChild(tbody);

            // Header
            let headerRow = document.createElement("tr");
            var zelle1 = document.createElement("th");
            var zelle2 = document.createElement("th");
            zelle1.textContent = "Temperatur"; 
            zelle2.textContent = "Luftdruck";  
            headerRow.appendChild(zelle1);
            headerRow.appendChild(zelle2);
            thead.appendChild(headerRow);

            // Body
            let bodyRow = document.createElement("tr");
            var zelle3 = document.createElement("td");
            var zelle4 = document.createElement("td");
            zelle3.textContent = data['temp']; 
            zelle4.textContent = data['pressure'];  
            bodyRow.appendChild(zelle3);
            bodyRow.appendChild(zelle4);
            tbody.appendChild(bodyRow);

        });
}

createTable("temp.json");
//time.sleep(5);
//createTable("temp.json");