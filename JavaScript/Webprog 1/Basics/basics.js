    document.writeln("<p>Ein neuer Absatz</p>");
    console.log("Eine Ausgabe in die Konsole");

    // TODO: Weitere Datentypen
    var word = "test";
    var zahl1 = 2006;
    var zahl2 = 1.562;
    var bool = true;
    document.writeln("typeof(" + word + ")=" + typeof(word) + "<br />");
    document.writeln("typeof(" + zahl1 + ")=" + typeof(zahl1) + "<br />");
    document.writeln("typeof(" + zahl2 + ")=" + typeof(zahl2) + "<br />");
    document.writeln("typeof(" + bool + ")= "  + typeof(bool) +  "<br />");
      
    // TODO: Syntaxfehler

            //console.log(das ist toll);

    // TODO: Indexbasierte Arrays

    var wordArray = ["Paul", "Tim", "Nico", "Wobitz", "Marvin"];

    document.writeln("<h2>Meine Liste mit Namen</h2>");
    document.writeln("<ul><li>" + wordArray[0] + "</li>");
    for (let i = 1; i < 4; i++) {
      document.writeln("<li>" + wordArray[i] + "</li>");
    }
    document.writeln("<li>" + wordArray[4] + "</li> </ul>");

    // TODO: Assoziative Arrays

    var abkuerzungen = [];
    abkuerzungen["html"] = "Hyper Text Markup Language";
    abkuerzungen["css"] = "cascading style sheet";
    abkuerzungen["cpu"] = "central processung unit";
    abkuerzungen["gpu"] = "graphics processing unit";
    abkuerzungen["SoC"] = "System on a chip";


    document.writeln("<h2>Abkürzungstabelle</h2>");
    document.writeln("<table><tr><td>HTML</td><td>" + abkuerzungen["html"] + "</td></tr>");
    document.writeln("<tr><td>CSS</td><td>" + abkuerzungen["css"] + "</td></tr>");
    document.writeln("<tr><td>CPU</td><td>" + abkuerzungen["cpu"] + "</td></tr>");
    document.writeln("<tr><td>GPU</td><td>" + abkuerzungen["gpu"] + "</td></tr>");
    document.writeln("<tr><td>SoC</td><td>" + abkuerzungen["SoC"] + "</td></tr></table>");
