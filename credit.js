function multiplyEveryOther(number) {
    let strOfNumber = number.toString();
    let arrayOfDigits = [];
    for (let i =strOfNumber.length -1; i >=0; i--) {
        arrayOfDigits.push(strOfNumber[i]);
    }
    console.log(arrayOfDigits[5]);

}
multiplyEveryOther(123456);