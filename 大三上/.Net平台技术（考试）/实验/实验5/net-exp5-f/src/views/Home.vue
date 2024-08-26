<template>
    <div id="home">
        <div class="page-wrapper" id="introduce">
            <div class="page-div">
                <h1>脚手架</h1>
                <p>
                    现代前端是一种依托于Html5 + CSS3 + ES的前端技术。其中，Html5是一种标签化的语言，本实验所有页面均使用Html5技术制作；CSS3是描述Html5标签显示样式的语言，
                    不过单纯的CSS并不好用，所以本次使用的是CSS的超集：LESS技术；ES指的是ECMA Script，其前身是Javascript。本次课程使用的语言版本是2019年制定的ES10。
                </p>
            </div>
        </div>
        <a-back-top />
    </div>
</template>

<script setup>
</script>

<style lang="less">
@import "@/assets/word-like.less";
@import "@/assets/paper.less";

#home {
    width: 793px;
    margin: 20px auto;
    color: #000;
    font-size: 16px;
}
</style>