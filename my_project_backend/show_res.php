<?php
// Параметры подключения к базе данных MySQL
$host = 'localhost';  // Адрес сервера MySQL
$dbname = 'my_proj1';  // Имя базы данных
$user = 'root';  // Имя пользователя
$password = '';  // Пароль

try {
    // Подключение к базе данных MySQL
    $dsn = "mysql:host=$host;dbname=$dbname;charset=utf8";
    $options = [
        PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    ];
    $db = new PDO($dsn, $user, $password, $options);

    // Выполняем запрос
    $stmt = $db->query("SELECT * FROM file_processor_File");

    // Получаем результаты
    $result = $stmt->fetchAll();

    // Выводим результаты
    foreach ($result as $row) {
        echo "Имя файла: " . $row['filename'] . "<br>";
        echo "Дата загрузки: " . date('Y-m-d H:i:s', strtotime($row['uploaded_at'])) . "<br>";
        echo "Результат: " . nl2br($row['result']) . "<br><br>";
    }

    // Выполняем запрос с использованием подготовленного выражения
    $stmt = $db->prepare("SELECT filename, uploaded_at, result FROM file_processor_File");
    $stmt->execute();

    // Получаем результаты
    $results = $stmt->fetchAll();

    // Преобразуем массив результатов в JSON
    $jsonData = json_encode($results, JSON_PRETTY_PRINT | JSON_UNESCAPED_UNICODE);

    // Определяем путь к JSON-файлу
    $jsonFilePath = __DIR__ . '/results.json';

    // Сохраняем результаты в JSON-файл
    file_put_contents($jsonFilePath, $jsonData);
    
    // Выводим сообщение об успешном сохранении
    echo "Результаты успешно сохранены в файле '$jsonFilePath'";
} catch (PDOException $e) {
    echo "Ошибка подключения: " . $e->getMessage();
}
?>