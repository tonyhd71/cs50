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
        //console.log("there are " + numQuarters + " quarters"); 
        numDimes = calculateDimes();
        numNickels = calculateNickels();
        console.log(numDimes + " dimes there are and there are " + centsLeft + " cents left and " + numQuarters + " quarters"); 
        numPennies = calculatePennies;
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
    centsLeft -= numNickels*5;
}
function calculateNickels() {
    centsLeft -= numDimes*10;
    //console.log(centsLeft + " cents are left"); 
    numNickels = Math.trunc(centsLeft/5);
    //console.log("there are " + numNickels + " nickels");
    return numNickels;

}
function calculateDimes() {
    centsLeft = cents - numQuarters*25;
    numDimes = Math.trunc(centsLeft/10);
    return numDimes;
}
function calculateQuarters() {
    numQuarters = Math.trunc(cents/25);
    return numQuarters;
}
getCents();