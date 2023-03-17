//perform different javascript functions depending on what page we're on:

// get html file name:
let fileName = location.href.split("/").slice(-1);
//select items needed in the dom
let name = document.getElementsByClassName("name");
let contact = document.getElementsByClassName("contact");
let backgroundVideo = document.getElementById("myVideo");


//set logic for changing the background video
let counter = 0;


//if we're on the homepage, do the following:
if(fileName[0] === 'index.html')
{
  //set background opacity
  backgroundVideo.style.opacity = "0.65";

  //change the color of the footer text to white
  name[0].style.color = "#FFFFFF";
  contact[0].style.color = "#FFFFFF";


  //create a function that will change the source of the background video, but changing the counter
  function videoChanger() {
    counter ++;
    if (counter % 2 != 0)
     {
       backgroundVideo.src = "https://res.cloudinary.com/dwxery2ci/video/upload/v1668719638/Cs50%20Homepage/Ocean_waves_splashing_-_Morocco_Casablanca_z68qmn.mp4"
     }
     else
     {
       backgroundVideo.src ="https://res.cloudinary.com/dwxery2ci/video/upload/v1667577026/Cs50%20Homepage/VID_20221104_155417_gnontj.mp4"
     }
    backgroundVideo.style.opacity = '0.1';

    backgroundVideo.style.opacity = '0.15';
    setTimeout(function()
    {
      backgroundVideo.style.opacity = '0.25';
    }, 250);
    setTimeout(function()
    {
      backgroundVideo.style.opacity = '0.35';
    }, 250);
    setTimeout(function()
    {
      backgroundVideo.style.opacity = '0.45';
    }, 250);
    setTimeout(function()
    {
      backgroundVideo.style.opacity = '0.55';
    }, 250);
    setTimeout(function()
    {
      backgroundVideo.style.opacity = '0.65';
    }, 250);
  }

  //add a click listener onto my name, so we can change the background video
  name[0].addEventListener("click", videoChanger);

}




//if we're not, do the following:
else
{

  //Javascript logic for the photo carousels:
  let slideIndex = 1;
  showSlides(slideIndex);

  // Next/previous controls
  function plusSlides(n) {
    showSlides(slideIndex += n);
  }

  // Thumbnail image controls
  function currentSlide(n) {
    showSlides(slideIndex = n);
  }

  function showSlides(n)
  {
    let i;
    let slides = document.getElementsByClassName("slide");
    let dots = document.getElementsByClassName("dot");
    if (n > slides.length) {slideIndex = 1}
    if (n < 1) {slideIndex = slides.length}
    for (i = 0; i < slides.length; i++) {
      slides[i].style.display = "none";
    }

    slides[slideIndex-1].style.display = "block";

  }

   //create a function that will change the source of the background video
   function videoChanger()
   {
     counter ++;
     if (counter % 2 != 0)
     {
       backgroundVideo.src = "https://res.cloudinary.com/dwxery2ci/video/upload/v1668719638/Cs50%20Homepage/Ocean_waves_splashing_-_Morocco_Casablanca_z68qmn.mp4"
     }
     else
     {
       backgroundVideo.src ="https://res.cloudinary.com/dwxery2ci/video/upload/v1667577026/Cs50%20Homepage/VID_20221104_155417_gnontj.mp4"
     }
   }
    //add a click listener onto my name, so we can change the background video
   name[0].addEventListener("click", videoChanger);


}




