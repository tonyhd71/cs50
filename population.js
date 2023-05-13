let n; // starting llama population
let endingPopulation; // ending llama population
function retrieveStart() {
    n = prompt("Starting population of llamas: ", 0); 
    n = parseInt(n);
    if (n < 9) {
        console.log("Input number greater than 9");
        retrieveStart()
    } else {
        retrieveEnd();
    }
}
function retrieveEnd() {
    endingPopulation = prompt("Ending population of llama: ", 0);
    if (endingPopulation < n) {
        retrieveEnd();
        //console.log(n + " is the starting population, and cannot be less than the ending, which is " + endingPopulation);
    } else {
        console.log('good');
    }
}
function yearsToThresh() {
    
}
function totalYears() {
    
}
retrieveStart();


