document.addEventListener('DOMContentLoaded', () => {
    var addToCart = document.getElementById('add-to-cart');
    // let cooldownTime = 1000; // 1 second cooldown
    // let lastFireTime = 0;
    if (addToCart) {
        // let rect = addToCart.getBoundingClientRect();
        // let x = rect.left + rect.width / 2;
        // let y = rect.top + rect.height / 2;
        // let colors = ['#26ccff', '#a25afd', '#ff5e7e', '#88ff5a', '#fcff42', '#ffa62d', '#ff36ff'];
        addToCart.onclick = function () {
            // let currentTime = Date.now();
            // if (currentTime - lastFireTime < cooldownTime) {
            //     return;
            // }
            PlusCartCount();
            // for (let angle = 0; angle < 360; angle += 1) {
            //     let randomColor = colors[Math.floor(Math.random() * colors.length)];
            //     let randomVelocity = 20 + Math.random();
            //     let randomDrift = -0.5 + Math.random() * 1;

            //     confetti({
            //         angle: angle,
            //         origin: { x: x / window.innerWidth, y: y / window.innerHeight },
            //         particleCount: 1,
            //         spread: 30,
            //         startVelocity: randomVelocity,
            //         ticks: 50,
            //         decay: 0.95, // faster decay
            //         gravity: 0.5,
            //         drift: randomDrift,
            //         zIndex: 9999,
            //         colors: [randomColor]
            //     });
            // }

            // lastFireTime = currentTime;
        }
    }
});