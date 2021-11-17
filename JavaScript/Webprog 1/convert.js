const input = document.querySelector("#number");
const select = document.querySelector("select[name=radix]");
    
input.addEventListener('keyup', convert);
select.addEventListener('change', convert);    

    function convert() {
      // const -> konstant, let variabel
      const number = parseInt(input.value);
      const radix = parseInt(select.options[select.selectedIndex].value); // ist ein String ...
      const result = Number(number).toString(radix).toUpperCase(); // war klein geschrieben
      document.querySelector("output").value = result;
    }