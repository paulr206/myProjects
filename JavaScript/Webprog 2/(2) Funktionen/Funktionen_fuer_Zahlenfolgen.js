function range(start, end, step) {
    // wenn step nicht übergeben
    if (step === undefined) {
        step = 1;
    }
    var arr = new Array();
    for(let i = start; i <= end; i = i + step) {
        arr.push(i);
    }
    return arr;
}

function sum(arr) {
    var summe = 0;
    // wenn Array übergeben
    if(Array.isArray(arr)) {
        arr.forEach(element => {
            summe = summe + element;
        });
        return summe;
    }
    else {
        for(let i = 0; i < arguments.length; i++) {
            summe = summe + arguments[i];
        }
    return summe;
    }
}

console.log(sum(range(1, 10))); // → 55
console.log(sum(range(1, 10, 2))); // → 25
console.log(sum(1, 3, 5, 7, 9)); // → 25