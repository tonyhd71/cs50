let n; // starting llama population
let endingPopulation; // ending llama population
let y =0; //years to reach end input
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
        //console.log('good');
        yearsToThresh();
    }
}
/*Say we have a population of n llamas. Each year, n / 3 new llamas are born, and n / 4 llamas pass away.
For example, if we were to start with n = 1200 llamas, then in the first year, 1200 / 3 = 400 new 
llamas would be born and 1200 / 4 = 300 llamas would pass away. At the end of that year, we would have 
1200 + 400 - 300 = 1300 llamas.
To try another example, if we were to start with n = 1000 llamas, at the end of the year, 
we would have 1000 / 3 = 333.33 new llamas. We can’t have a decimal portion of a llama, though,
 so we’ll truncate the decimal to get 333 new llamas born. 1000 / 4 = 250 llamas will pass away, 
 so we’ll end up with a total of 1000 + 333 - 250 = 1083 llamas at the end of the year.
*/
function yearsToThresh() {
    console.log(n);
    while (n < endingPopulation) {
        n = n + ((Math.trunc(n/3))-(Math.trunc(n/4)));
        y++;
        //console.log(y);
        //return y;
    }
    alert("It will take " + y + " years to reach a llama population of " + endingPopulation);

}
function totalYears() {
    
}
retrieveStart();


