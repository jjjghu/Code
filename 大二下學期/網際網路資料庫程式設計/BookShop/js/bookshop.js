// 輪播圖版本 1 , 只需負責每過一陣子按下按鈕
// 缺點: 會沒有辦法顯示標題
// document.addEventListener('DOMContentLoaded', (event) => {
//     // 剛開始為0
//     let currentIndex = 0;
//     // 獲取所有按鈕連結
//     const nav = document.querySelectorAll('.slider-nav a');
//     // 紀錄下總共有多少頁面
//     const totalSlides = nav.length;
//     let autoPlayInterval = null;

//     // 跳轉到下一個圖片
//     function goToNextSlide() {

//         // 更新位置
//         currentIndex = (currentIndex + 1) % totalSlides;
//         // 按下按鈕
//         nav[currentIndex].click();
//     }
//     function startAutoPlay() {
//         if (!autoPlayInterval) {
//             autoPlayInterval = setInterval(goToNextSlide, 3000);
//         }
//     }
//     function stopAutoPlay() {
//         if (autoPlayInterval) {
//             clearInterval(autoPlayInterval);
//             autoPlayInterval = null;
//         }
//     }

//     // nav.forEach((link, value, array));

//     // 每一個nav都要監聽事件 (當前元素, 當前元素的index)
//     nav.forEach((link, index) => {
//         link.addEventListener('click', (event) => {
//             // 按下的時候滑動到最上面
//             window.scrollTo(0, 0);
//             // 被按下的時候更新currentIndex
//             currentIndex = index;
//         });
//     });

//     let observer = new IntersectionObserver((entries, observer) => {
//         entries.forEach(entry => {
//             // 當元素進入視窗時entry.isIntersecting為true，否則為false
//             if (entry.isIntersecting) {
//                 startAutoPlay();
//             } else {
//                 stopAutoPlay();
//             }
//         });
//     }, { threshold: 1.0 }); // 至少有100%的元素在視窗中

//     // 觀察輪播的容器
//     observer.observe(document.querySelector('.slider-wrapper'));

//     // 啟動自動播放
//     startAutoPlay();

//     // 設定觸發間隔
//     // setInterval(goToNextSlide, 3000); // 3000ms = 3 second
// });
// 輪播圖版本 2, 不會在轉換時跳轉到該位置, 失去了平滑動畫切換
document.addEventListener('DOMContentLoaded', () => {
    const slides = document.querySelectorAll('.slider img');
    const navLinks = document.querySelectorAll('.slider-nav a');
    let currentIndex = 0;
    let autoPlayInterval = null;

    function showSlide(index) {
        slides.forEach((slide, i) => {
            slide.style.display = i === index ? 'block' : 'none';
        });
        updateNav(index);
    }

    function updateNav(index) {
        navLinks.forEach((link, i) => {
            link.style.opacity = i === index ? '1' : '0.75';
        });
    }

    function goToNextSlide() {
        currentIndex = (currentIndex + 1) % slides.length;
        showSlide(currentIndex);
    }

    navLinks.forEach((link) => {
        link.addEventListener('click', (event) => {
            const index = parseInt(event.currentTarget.getAttribute('data-index'), 10);
            currentIndex = index;
            showSlide(index);
        });
    });

    function startAutoPlay() {
        autoPlayInterval = setInterval(goToNextSlide, 3000);
    }

    function stopAutoPlay() {
        if (autoPlayInterval) {
            clearInterval(autoPlayInterval);
        }
    }

    // 初始化
    showSlide(currentIndex);
    startAutoPlay();

    // 滑鼠進入就不播放, 離開就播放
    const sliderWrapper = document.querySelector('.slider-wrapper');
    sliderWrapper.addEventListener('mouseenter', stopAutoPlay);
    sliderWrapper.addEventListener('mouseleave', startAutoPlay);
});
