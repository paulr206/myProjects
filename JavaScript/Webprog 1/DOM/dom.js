// TODO: Code to access and manipulate the DOM.

      //Aufgabe 1
      const myList = document.querySelector("#myList");
      const anzahlKinderUl = myList.childNodes.length;
      console.log("Anzahl: " + anzahlKinderUl);

      //Aufgabe 2
      const a = myList.querySelector("a")
      console.log("Verweisziel: " + a.href);
      myList.querySelector("a").href = "https://www.umwelt-campus.de";
      console.log("Verweisziel neu: " + a.href);

      //Aufgabe 3
      a.text = "UCB";

      //Aufgabe 4
      const iMG = new Image();
      iMG.alt = "W3C";
      iMG.src = "http://www.w3.org/Icons/w3c_main.png";

      // Aufgabe 5
      const p = document.querySelector("p:nth-of-type(2)");
      p.replaceChild(iMG, p.firstChild);

      // Aufgabe 6
      //document.body.replaceChild(img, p);
