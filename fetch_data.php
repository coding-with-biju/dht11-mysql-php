<?php
include 'config.php';

$sql = "SELECT * FROM readings ORDER BY timestamp DESC LIMIT 10";
$result = $conn->query($sql);

$data = array();
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

echo json_encode($data);
$conn->close();
?>
