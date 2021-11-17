function intersection() {
    if (arguments.length > 1) {
        matches = arguments[0];
        let i = 1;
        while ( i < arguments.length) {
            let mystr = arguments[i];
            for (let j = 0; j < matches.length; j++) {
                if (!mystr.includes(matches[j])) {
                    matches.splice(matches.indexOf(matches[j]), 1);
                }
            }
        }
        return matches;
    }
    else {
        console.log("Intersection mit zu wenigen parametern aufgerufen.");
    }
}

function padStart(str, len, chars = " ") {
    let mystr = [];
    let count = 0;
    let padspace = len - str.length;
    while (count < padspace) {
        for (let i = 0; i < chars.length; i++) {
            mystr.push(chars[i]);
            count++;
            if (count == padspace) {
                break;
            }
        }
    }
    for (let i = 0; i < str.length; i++ ) {
        if (mystr.length < length) {
            mystr.push(str[i]);
        }
    }
    return mystr;
}

function pick(obj, args) {
    let myobj = obj;
    let keys = Object.keys(obj);
    for (const key in obj) {
        if (!args.includes(key)){
            delete myobj.key;
        }
    }
    return myobj;
}


export {intersection, padStart, pick};