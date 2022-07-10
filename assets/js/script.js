const hamb = document.querySelector(".hamb");
const nav = document.querySelector(".slide");

hamb.addEventListener("click", function() {
  nav.classList.toggle("right");
})