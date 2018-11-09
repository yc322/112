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
$flag=$_POST['flag'];


$sum = 0;
for ($i = 0; $i < 9; $i++) {
    for ($j = 0; $j < 9; $j++) {
        $sum = $sum + 1;
        if(!empty($_POST['fig'.$sum])) {
            $sd_flag[$i][$j]=0;
            $sd_array[$i][$j] = intval($_POST['fig' . $sum]);
        }
        else if(!empty($_POST['tex'.$sum])){
            $sd_flag[$i][$j]=1;//the number from init
            $sd_array[$i][$j]=$_POST['tex'.$sum];
        }
        else{
            $sd_flag[$i][$j]=0;//the number user input
            $sd_array[$i][$j]=intval($_POST['user'.$sum]);

        }
    }
}



function sd_correct($sd_array){
    $tmp=array();
    //echo "&&&&&&&&&&&&&&&";
    for($i=0;$i<9;$i++){
        array_splice($tmp,0,9);
        for($j=0;$j<9;$j++){
            $t=$sd_array[$i][$j];
            if($sd_array[$i][$j]==0) {return 0;}
            if($tmp[$t]==0) $tmp[$t]++;
            else {return 0;}
        }
    }
    for($j=0;$j<9;$j++){
        array_splice($tmp,0,9);
        for($i=0;$i<9;$i++){
            $t=$sd_array[$i][$j];
            if($sd_array[$i][$j]==0) {return 0;}
            if($tmp[$t]==0) $tmp[$t]++;
            else {return 0;}
        }
    }
    //$tmp2=array();
    for($i=0;$i<3;$i++){
        array_splice($tmp,0,9);

        for($j=0;$j<3;$j++){
            for($k=0;$k<9;$k++){
                $a=$sd_array[3*$i+$k/3][3*$j + $k%3];
                if(tmp[$a]==0) tmp[$a++];
                else {return 0;}
            }
        }
    }
    return 1;
}
//$regld=implode(",", $sd_array);

print_r($sd_array);
?>

<div align="center">
    <h1>结果</h1>
    <form id="form" action="sudoku_judge.php" method="post">
    <table border="0" >
        <?php
        //error_reporting(E_ALL & ~E_NOTICE);
        if(sd_correct($sd_array)==1){
            echo '<script language="javascript">location.href="sudoku_correct.php"</script>';

        }

        if(sd_correct($sd_array)==0 && $flag!=1){
        	$sum=0;
            for($i=0;$i<9;$i++){
                echo "<tr>";
                for($j=0;$j<9;$j++){
                    $sum=$sum+1;
                    if($sd_array[$i][$j]==NULL){
                        echo "<td><input type=\"text\" name=\"fig".$sum."\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"\"></td>";
                    }
                    else if($sd_flag[$i][$j]==1){
                        echo "<td><input style='background-color: #FC8B9B ' type=\"text\" name=\"tex".$sum. "\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"".$sd_array[$i][$j]."\" readOnly=\"true\"></td>";
                    }else{
                        echo "<td><input style='background-color:#CBA8A8' type=\"text\" name=\"user".$sum. "\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"".$sd_array[$i][$j]."\"></td>";
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
        elseif($flag==1){
            $sum=0;
            for($i=0;$i<9;$i++){
                echo "<tr>";
                for($j=0;$j<9;$j++){
                    $sum=$sum+1;
                    if($sd_array[$i][$j]!=NULL && $sd_flag[$i][$j]==1){
                        echo "<td><input style='background-color: #FC8B9B' type=\"text\" name=\"tex".$sum. "\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"".$sd_array[$i][$j]."\" readOnly=\"true\"></td>";

                    }
                    else{
                        echo "<td><input type=\"text\" name=\"fig".$sum."\" max=\"9\" min=\"1\" maxlength=\"1\" size=\"1\" value=\"\"></td>";
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
    <input type="submit" value="提交" style="width: 50px;height: 30px;">&nbsp;&nbsp;&nbsp;
    <input id="reset" type="hidden" name="flag" value=0 />
    <input type="submit" onclick="sd_reset()" value="重置" style="width:50px;height:30px" />
    <script>
        function sd_reset(){
            var form=document.forms[0];
            form.reset.value = 1;
            form.submit();
        }
    </script>

</div>
<script>
    function goback(){
        history.go(-1);
    }
</script>
</body>
</html>

