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
        numDimes = calculateDimes();
        numNickels = calculateNickels();
        numPennies = calculatePennies();
        alert("Pennies: " + numPennies + '\n' +
        "Nickels: " + numNickels + '\n' +
        "Dimes: " + numDimes + '\n' +
        "Quarters: " + numQuarters + '\n');
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
    numPennies = Math.trunc(centsLeft/1);
    return numPennies;
}
function calculateNickels() {
    centsLeft -= numDimes*10;
    numNickels = Math.trunc(centsLeft/5);
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