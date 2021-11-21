//'use strict'
        // Aufgabe 1
        var person1 = new Object();
        person1.name = "Greg";
        person1.age = 25;
        person1.greet= function greet() {
            console.log("Hi");
        }
        person1.greet();

        // Aufgabe 2
        var person2 = {
            name: "Ben",
            age: 18,
            greet: function greet2() {
            console.log("Servus");
        }
        };
        
        person2["greet"]();
        person2.greet();

        // Aufgabe 3
        console.log(person1.name);
        console.log(person2["name"]);
        console.log(person1.age);
        console.log(person2["age"]);

        // Aufgabe 4
        delete person2.age;

        // Aufgabe 5
        Object.defineProperty(person2, "name", {
            writable : false
        });
        person2.name = "Werner";
        console.log(person2["name"]);
        // Fehler kann nicht eine read only Variable beschreiben -> ohne strict wird Ben auf Konsole ausgegeben

        // Aufgabe 6
        Object.seal(person2);
        person2.size = 1.81;
        console.log(person2.size);
        // ohne strict: undefined - mit strict: 