let n; // starting llama population
let endingPopulation; // ending llama population
let y = 0; //years to reach end input
function retrieveStart() {
    n = prompt("Starting population of llamas: ", 0); 
    n = parseInt(n);
    if (n < 9) {
        console.log("Input number greater than 9");
        retrieveStart();
    } else {
        retrieveEnd();
    }
}
function retrieveEnd() {
    endingPopulation = prompt("Ending population of llama: ", 0);
    if (endingPopulation < n) {
        retrieveEnd();
    } else {
        yearsToThresh();
    }
}
function yearsToThresh() {
    while (n < endingPopulation) {
        n = n + ((Math.trunc(n/3))-(Math.trunc(n/4)));
        y++;
    }
    alert("It will take " + y + " years to reach a llama population of " + endingPopulation);
}
retrieveStart();


