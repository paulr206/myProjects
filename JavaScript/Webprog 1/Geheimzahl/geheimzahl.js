/* Nach dem Laden der Seite:
      1. Den Absenden-Button deaktivieren.
      2. Einen Event-Handler für einen Tastendruck im Eingabefeld registrieren.
      3. Dem Eingabefeld den Fokus geben.
    */
      window.addEventListener("load", function () {
        document.getElementById("go").disabled = true;
        const input = document.getElementById("pin");
        input.addEventListener("keyup", checkPin);
        input.focus();
      });
  
      /* Im Event-Handler soll Folgendes gemacht werden:
        1. Falls etwas anderes als die Ziffern 0 bis 9 eingegeben werden:
          a) Das div-Element mit der Fehlermeldung anzeigen.
          b) Dem Eingabefeld die CSS-Klasse "invalid" zuweisen.
        2. Falls die Eingabe nur aus den Ziffern 0 bis 9 besteht:
          a) Das div-Element mit der Fehlermeldung ausblenden.
          b) Dem Eingabefeld die CSS-Klasse "invalid" entziehen.
        3. Falls genau 6 Ziffern eingegeben wurden, soll der Absenden-Button aktiviert werden,
           ansonsten soll er deaktiviert werden. 
      */
      function checkPin(e) {
        const input = e.target;
        //const input = document.getElementById("pin");
        const div = document.getElementById("error");
        //if (!/^\d*$/.test(input.value)) {
        if (!isValid(input.value)) {
          div.style.display = "block";
          input.className = "invalid";
          return;
        }
        else {
          div.style.display = "none";
          input.className = "";
        }
        const submit = document.getElementById("go");
        //submit.disabled = !/^\d{6}$/.test(input.value);
        submit.disabled = input.value.length !== 6;
      }
  
      function isValid(number) {
        for (let i = 0; i < number.length; i++) {
          const charCode = number.charCodeAt(i);
          // Die Ziffern 0 bis 9 haben die Unicode-Werte 48 bis 57.
          if (charCode < 48 || charCode > 57) return false;
        }
        return true;
      }