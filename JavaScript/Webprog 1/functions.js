function range(start, end) {
    var array = [];
    var differenz = end - start;
    for(var i = 0; i <= differenz; i++) {
        array[i] = start + i;
    }
    return array;
}

function sum(zahlen) {
    var summe = 0;
    for(var i = 0; i < zahlen.length; i++) {
        summe = zahlen[i] + summe;
    }
    return summe;
}


var test = range(3, 8);

for(var i = 0; i<test.length; i++){
    console.log(test[i]);
}

console.log("Die Summe beträgt: " + sum(test));