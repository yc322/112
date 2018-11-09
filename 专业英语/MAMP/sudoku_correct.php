<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>耶耶耶</title>
</head>
<body>
<style>
    .form{
        width: 395px;
        height: 200px;
    }
    input{
        width: 30px;
        height: 30px;
        font-size: 18px;
        text-align: center;
    }
    td{

    }
</style>

<div align="center">
    <p>喵喵喵</p>
    <p>
        <img src="2.jpeg" width="165" height="100" />
        <img src="4.jpg" width="165" height="100" />

    </p>
    <?php $url ='my_sudoku.php';?>
    <script type="text/javascript">
        function again(){
            window.location.href='<?=$url ?>';
        }
    </script>
    <button class="button" id="add123" onclick="again()">再来一局</button>
    <?php $url ='index.php';?>
    <script type="text/javascript">
        function again(){
            window.location.href='<?=$url ?>';
        }
    </script>
    <button class="button" id="add123" onclick="again()">返回主页</button>
    
</div>
<script>
    function goback(){
        history.go(-1);
    }
</script>
</body>
</html>

