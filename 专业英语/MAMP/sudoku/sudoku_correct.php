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

$sd_array = array();
for ($i = 0; $i < 20; $i++) {
    for ($j = 0; $j < 20; $j++) {
        $sd_array[$i][$j] = 0;
    }
}

$sum = 0;
for ($i = 0; $i < 9; $i++) {
    for ($j = 0; $j < 9; $j++) {

        $sum = $sum + 1;
        /**
         * 要先判断输入的类型，只能是1-9的数字
         */
        if (empty($_POST['fig' . $sum])) {
            $sd_array[$i][$j] = 0;
        } 
        else {
            $sd_array[$i][$j] = intval($_POST['fig' . $sum]);
        }
    }
}


function sd_correct($sd_array){
	$tmp=array();
	for($i=0;$i<9;$i++){
		array_splice($tmp,0,9);
		for($j=0;$j<9;$j++){
			if($sd_array[$i][$j]==0) return 0;
			if($tmp[j]==0) $tmp[j]++;
			else return 0;
		}
	}
	for($j=0;$j<9;$j++){
		array_splice($tmp,9);
		for($i=0;$i<9;$i++){
			if($sd_array[$i][$j]==0) return 0;
			if($tmp[i]==0) $tmp[i]++;
			else return 0;
		}
	}
}


?>

<div align="center">
    <h1>结果</h1>
    <table border="0" >
        <?php
        if(sd_correct($sd_array)==0){
        	$sum=0;
        	for($i=0;$i<9;$i++){
        		echo "<tr>";
        		for($j=0;$j<9;$j++){
        			$sum=$sum+1;
        			if($sd_array[$i][$j]==0){
        				echo "<td><input  type=\"text\" value=\""."  "."\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" ></td>";
        			}
        			else{
        				echo "<td><input style='background-color: #cac5c9' type=\"text\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"".$sd_array[$i][$j]."\"></td>";
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

