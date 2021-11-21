const firstPara = document.querySelector("p");
    const secondPara = document.createElement("p");
    secondPara.textContent = "Hier wurde der zweite Paragraph eingefügt";
    firstPara.appendChild(secondPara);


    const list = document.querySelector("ul");
    const secondLI = list.querySelector("li:nth-of-type(2)");
    const thirdLI = list.querySelector("li:nth-of-type(3)");
    list.removeChild(secondLI);
    if(true){
        thirdLI.style.color = "red";
    }