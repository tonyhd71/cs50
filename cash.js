let cents;
let numPennies;
let numNickels;
let numDimes;
let numQuarters;

function getCents() {
    cents = prompt("How many cents", 1);
    cents = parseInt(cents);
    let isValid = validChange();
    if (isValid === true) {
        numQuarters = calculateQuarters();
        console.log("there are " + numQuarters + " quarters"); // here so far 
    }
}
function validChange() {
    if (cents <0 || cents > 99) {
        return false;
    } else {
        return true;
    }
}
function calculatePennies() {
    
}
function calculateNickels() {

}
function calculateDimes() {

}
function calculateQuarters() {
    if (cents < 25) {
        numQuarters = parseInt(0);
        //console.log(numQuarters);
    } else if (cents >= 25 && cents < 50) {
        numQuarters = parseInt(1);
        //console.log(numQuarters);
    } else if (cents >=50 && cents < 75) {
        numQuarters = parseInt(2);
       // console.log(numQuarters);
    } else if (cents >=75 && cents < 99) {
        numQuarters = parseInt(3);
        //console.log(numQuarters);
    }
    return numQuarters;
    //console.log(numQuarters);
}
getCents();