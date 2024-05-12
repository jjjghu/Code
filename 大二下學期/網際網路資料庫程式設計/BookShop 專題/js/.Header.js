document.addEventListener('DOMContentLoaded', () => {
    // 黑暗模式切換按鈕, 都在Loaded之後確認按紐存在, 再加入功能
    // toggle不知為何不能使用, 因此使用add remove 判斷做到相同的效果
    var themeIcon = document.getElementById('themeIcon');
    if (themeIcon) {
        themeIcon.onclick = function () {
            document.body.classList.toggle('dark-theme');
            themeIcon.classList.toggle('bx-brightness');
            themeIcon.classList.toggle('bx-moon');
            // 用 js 將 cookie 存放在瀏覽器中
            if (document.body.classList.contains('dark-theme')) {
                document.cookie = "theme=dark-theme; path=/";
            } else {
                document.cookie = "theme=none; path=/";
            }
        }
    }
    // 顯示購物車頁面
    var toggleCart = document.getElementById('toggleCart');
    if (toggleCart) {
        toggleCart.onclick = function () {
            var cartPreview = document.getElementById('cart-preview');
            // 將 cart-preview 當中的 display 設定為 flex
            if (cartPreview) {
                cartPreview.style.display = cartPreview.style.display === 'flex' ? 'none' : 'flex';
            }

        }
    }

    // 商品數量歸零刪除, 數量減少
    document.querySelectorAll('.decrement').forEach(function (button) {
        button.addEventListener('click', function () {
            var input = this.parentNode.querySelector('input[type=number]');
            input.stepDown();
            MinusCartCount();
            if (input.value == 0) {
                // 如果數量為 0，則移除該商品
                this.closest('.preview-product').remove();
            }
        });
    });

    // 商品數量增加
    document.querySelectorAll('.increment').forEach(function (button) {
        button.addEventListener('click', function () {
            this.parentNode.querySelector('input[type=number]').stepUp();
            PlusCartCount();
        });
    });
});
function PlusCartCount() {
    var cartCount = document.getElementById('cart-count');
    if (cartCount.innerText == 0) {
        cartCount.style.display = 'block';
    }
    ++cartCount.innerText;
}
function MinusCartCount() {
    var cartCount = document.getElementById('cart-count');
    if (cartCount.innerText > 0) {
        --cartCount.innerText;
    }
    if (cartCount.innerText <= 1) {
        cartCount.style.display = 'none';
    }
}