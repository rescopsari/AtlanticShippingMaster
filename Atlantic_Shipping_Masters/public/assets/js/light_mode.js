const lightModBbutton = document.getElementById("light-mode");
const body = document.body;
const label = document.getElementById("light-label");
const sun = document.getElementById("sun");
const moon = document.getElementById("moon");

const theme = localStorage.getItem("theme");

// const mainBodyElement = body.children;
// console.log(mainBodyElement);

if (theme) {
    body.className = theme;
}

lightModBbutton.onclick = () => {
    if (body.className === "dark") {
        body.className = "light";
        sun.style.display = "none";
        moon.style.display = "block";
        label.innerHTML = "Dark Mode";
        localStorage.setItem("theme", "light");
    } else {
        body.className = "dark";
        moon.style.display = "none";
        sun.style.display = "block";
        label.innerHTML = "Light Mode";
        localStorage.setItem("theme", "dark");
    }
}
