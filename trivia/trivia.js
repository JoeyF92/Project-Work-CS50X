let answer = document.getElementById("answer");
let answer2 = document.getElementById("answer2");
let button = document.querySelectorAll("button");
let textBox = document.getElementById("textbox");
let body = document.querySelector("body");

// here we're creating the function for when a user clicks the button
function userClick(event)
{
    let trigger = event.srcElement;
    //if the button clicked is triple equals the right answer do this
    if (trigger.innerHTML === "9 million"){
        //first reset the color of all buttons
        for( let i = 0; i < button.length; i++){
            button[i].style.backgroundColor = "#d9edff";
        }
        //then change the button color to green
        trigger.style.backgroundColor = "green";
        //display correct!
        answer.innerHTML = "Correct!";
        answer.style.display = "block";


    }
    // if we click on the incorrect button
    else {
        //reset the button colours
        for( let i = 0; i < button.length; i++){
            button[i].style.backgroundColor = "#d9edff";
        }
        // change the color to red of the button clicked and display incorrect
        trigger.style.backgroundColor = "Red";
        answer.innerHTML = "Incorrect!";
        answer.style.display = "block";
    }
}

// this is the function for when the user clicks on the submit button from section 2
function part2(event)
{
    //if the contents of text box in lower case triple equals fever - then show correct and change textbox green
    if(textBox.value.toLowerCase() === "fever")
    {
        textBox.style.backgroundColor = "Green";
        answer2.innerHTML = "Correct!";
        answer2.style.display = "block";
    }
    //else show incorrect and textbox red
    else
    {
        textBox.style.backgroundColor = "Red"
        answer2.innerHTML = "Incorrect!";
        answer2.style.display = "block";
    }


}