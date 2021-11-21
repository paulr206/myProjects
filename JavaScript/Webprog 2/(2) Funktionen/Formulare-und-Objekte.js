const Katze = {
    name: "Findus",
    besitzer: "Pettersson",
    alter: 4,
    gewicht: 4.5,
    rasse: "Straßenmischung"
  };
  function initForm() {
      console.log(this);
      const elements = document.getElementsByTagName("input");
      for (let i=0; i < elements.length; i++) {
          elements[i].value = Katze[elements[i].name];
      }
  }
  window.onload = initForm;