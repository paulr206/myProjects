    // Returns a function for creating signed magnitude representations (SMR).
    function createSMRFunction (numberOfBits) {
        // TODO
        function isInRange(z) { if(z >= start && z <= end){ return true; } return false; }
        var distance = Math.pow(2, numberOfBits)-2;
        var start = -(distance/2);
        var end = distance/2;
         return function(dezimalzahl){
             // postive Zahl
             if((isInRange(dezimalzahl) && dezimalzahl > 0) || Object.is(+0, dezimalzahl)) {
                 var zwerg = dezimalzahl.toString(2);
                 for(var i = zwerg.length; i < numberOfBits; i++){
                     zwerg = '0'+ zwerg;
                 }
                 return zwerg;
             }
             // negative Zahl
             else if((isInRange(dezimalzahl) && dezimalzahl < 0) || Object.is(-0, dezimalzahl)){
                 dezimalzahl *= -1;
                 var zwerg = dezimalzahl.toString(2);
                 for(var i = zwerg.length; i < numberOfBits-1; i++){
                     zwerg = '0'+ zwerg;
                 }
                 zwerg = '1' + zwerg;
                 return zwerg;
             }
             else {
                 console.log("Paramater " + dezimalzahl + " must be a number between" + start + " and " + end);
             }
         }
     }
     
     let numberOfBits = 3;
     let createSignedMagnitudeRepresentation = createSMRFunction(numberOfBits);
     console.log(createSignedMagnitudeRepresentation(5)); // Parameter 5 must be a number between -3 and +3.
     for (let i = 0, n = Math.pow(2, numberOfBits - 1) - 1; i <= n; i++) {
         console.log('+' + i + ' = ' + createSignedMagnitudeRepresentation(i));
         console.log('-' + i + ' = ' + createSignedMagnitudeRepresentation(-i));
         
     }
         console.log('-43 = ' + createSMRFunction(8)(-43));
     /*
     +0 = 000
     -0 = 100
     +1 = 001
     -1 = 101
     +2 = 010
     -2 = 110
     +3 = 011
     -3 = 111
     -43 = 10101011
     */