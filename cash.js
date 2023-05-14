let cents;
let numPennies;
let numNickels;
let numDimes;
let numQuarters;
let centsLeft;

function getCents() {
    cents = prompt("How many cents", 1);
    cents = parseInt(cents);
    let isValid = validChange();
    if (isValid === true) {
        numQuarters = calculateQuarters();
        console.log("there are " + numQuarters + " quarters"); 
        numDimes = calculateDimes();
        console.log(numDimes + " dimes there are and there are " + centsLeft + "cents left"); //here so far
        numNickels = calculateNickels();
    }
}
function validChange() {
    if (cents <0 || cents > 99) {
        getCents();
    } else {
        return true;
    }
}
function calculatePennies() {
    
}
function calculateNickels() {

}
function calculateDimes() {
    centsLeft = cents - numQuarters*25;
    if (centsLeft <10) {
        numDimes = parseInt(0);
    } else if (centsLeft >=10) {
        numDimes = Math.trunc(centsLeft/10);
    }
    return numDimes;
}
function calculateQuarters() {
    numQuarters = Math.trunc(cents/25);
    return numQuarters;
}
getCents();