<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>数独生成</title>
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

<?php

$templet = '618923754974651832523847961732516498491738625865492317146289573389175246257364189';
$sd_array = array();
for ($i = 0; $i < 9; $i++) {
    for ($j = 0; $j < 9; $j++) {
        $sd_array[$i][$j] = $templet[$i *9 +$j];
    }
}

/*create a new sudoku*/
for($t=0;$t<10;$t++){
    $tmp1=rand(0,8);
    $tmp2=rand(0,8);
    if($t %2 ==0){
        list($sd_array[$tmp1],$sd_array[$tmp2])=array($sd_array[$tmp2],$sd_array[$tmp1]);
    }

    else{
        for($i=0;$i<9;$i++){
            list($sd_array[$i][$tmp2],$sd_array[$i][$tmp1])=array($sd_array[$i][$tmp1],$sd_array[$i][$tmp2]);
        }
    }
}

for($t=0;$t<20;$t++){
    $tmp1=rand(0,8);
    $tmp2=rand(0,8);
    if($sd_array[$tmp1][$tmp2]!=0){
        $sd_array[$tmp1][$tmp2]=0;
    }
}
?>

<div align="center">
    <h1>生成数独</h1>
    <form action "sudoku_correct.php" method="post">
    <table border="0" >
        <?php
        $sum = 0;
        for ($i=0;$i<9;$i++){
            echo "<tr>";
            for ($j=0;$j<9;$j++){
                $sum = $sum + 1;
                if($sd_array[$i][$j]==0){
                    echo "<td><input  type=\"text\" value=\""."  "."\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" ></td>";
                }else{
                    echo "<td><input style='background-color: #cac5c9' type=\"text\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"".$sd_array[$i][$j]."\"></td>";
                }
                if($sum%3==0){
                    echo "<td></td>";
                }
            }
            echo "</tr>";
            if($sum%27==0){
                echo "<tr></tr><tr></tr>";
            }
        }

        ?>
    </table>
    <input type="button" value="返回" style="width: 50px;height: 30px;" onclick="goback()">
</div>
<script>
    function goback(){
        history.go(-1);
    }
</script>
</body>
</html>

