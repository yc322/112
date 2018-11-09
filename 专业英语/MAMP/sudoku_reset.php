<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>数独破解</title>
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
error_reporting(E_ALL & ~E_NOTICE);
$sd_array=array();
$sd_flag=array();

$sum = 0;
for ($i = 0; $i < 9; $i++) {
    for ($j = 0; $j < 9; $j++) {
        $sum = $sum + 1;
        if(!empty($_POST['fig'.$sum])) {
            $sd_flag[$i][$j]=0;//the number from init
            $sd_array[$i][$j] = intval($_POST['fig' . $sum]);
        }
        else if(!empty($_POST['tex'.$sum])){
            $sd_flag[$i][$j]=1;//the number from init
            $sd_array[$i][$j]=$_POST['tex'.$sum];
            continue;
        }
        else{
            $sd_flag[$i][$j]=0;//the number user input
            $sd_array[$i][$j]=intval($_POST['user'.$sum]);

        }
    }
}


//$regld=implode(",", $sd_array);

print_r($sd_array);
?>

<div align="center">
    <h1>结果</h1>
    <form action="sudoku_judge.php" method="post">
    <table border="0" >
    <?php
    //error_reporting(E_ALL & ~E_NOTICE);
    	$sum=0;
        for($i=0;$i<9;$i++){
            echo "<tr>";
            for($j=0;$j<9;$j++){
                $sum=$sum+1;
                if($sd_flag[$i][$j]!=1){
                    echo "<td><input type=\"text\" name=\"fig".$sum."\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"\"></td>";
                }
                if($sd_flag[$i][$j]==1){
                    echo "<td><input style='background-color: #cac5c9' type=\"text\" name=\"tex".$sum. "\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"".$sd_array[$i][$j]."\" readOnly=\"true\"></td>";
                }
                if($sum%3==0){
                    echo"<td></td>";
                }
            }
            echo "</tr>";
            if($sum%27==0){
                echo"<tr></tr><tr></tr>";
            }
        }
    ?>
    </table>
    <input type="submit" value="提交" style="width: 50px;height: 30px;">&nbsp;&nbsp;&nbsp;
    <script>
        function reset(){
            document.location.href="sudoku_reset.php";
        }
    </script>
    <input type="button" onclick="reset()" value="重置" style="width:50px;height:30px" />

</div>
<script>
    function goback(){
        history.go(-1);
    }
</script>
</body>
</html>

