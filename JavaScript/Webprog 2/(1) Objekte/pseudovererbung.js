//Schreiben Sie eine Funktion mixin mit den beiden Parametern receiver und supplier. Die Funktion kopiert alle aufzählbaren Eigenschaften des zweiten Objekts auf das erste Objekt, sofern diese Eigenschaften direkt auf dem zweiten Objekt gesetzt sind (eigene Eigenschaften).
function mixin(receiver, supplier) {
    var properties = Object.keys(supplier);
    var i, len;
    for (i=0, len=properties.length; i < len; i++){
        if(supplier.hasOwnProperty(properties[i])){
            console.log(properties[i]);
            receiver[i] = supplier[receiver[i]];
        }
    }
};
const receiver = { name: "Max" };
const supplier = { role: "developer", lang: "en" };
mixin(receiver, supplier);
console.log(Object.getOwnPropertyDescriptor(receiver, "role"))
receiver.name = "Marvin";
console.log(receiver); // Object { name: "Max", role: "developer", lang: "en" }