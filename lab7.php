<?php

if (isset($_SESSION['id'])) {
    // Get input and validate it as an integer (assuming user_id is numeric)
    $id = $_SESSION['id'];
    if (!filter_var($id, FILTER_VALIDATE_INT)) {
        die('<pre>Invalid ID format.</pre>');
    }

    switch ($_DVWA['SQLI_DB']) {
        case MYSQL:
            // Prepare statement to mitigate SQL Injection
            $stmt = mysqli_prepare($GLOBALS["___mysqli_ston"], "SELECT first_name, last_name FROM users WHERE user_id = ? LIMIT 1;");
            if ($stmt === false) {
                die('<pre>Database error: Failed to prepare statement.</pre>');
            }

            mysqli_stmt_bind_param($stmt, "i", $id);
            mysqli_stmt_execute($stmt);
            mysqli_stmt_bind_result($stmt, $first, $last);

            if (mysqli_stmt_fetch($stmt)) {
                echo "<pre>ID: {$id}<br />First name: {$first}<br />Surname: {$last}</pre>";
            } else {
                echo "<pre>No user found with ID: {$id}</pre>";
            }

            mysqli_stmt_close($stmt);
            mysqli_close($GLOBALS["___mysqli_ston"]);
            break;

        case SQLITE:
            global $sqlite_db_connection;

            // Prepare statement
            $query = "SELECT first_name, last_name FROM users WHERE user_id = :id LIMIT 1;";
            $stmt = $sqlite_db_connection->prepare($query);
            if ($stmt === false) {
                die('<pre>Database error: Failed to prepare statement.</pre>');
            }

            // Bind parameter
            $stmt->bindValue(':id', $id, SQLITE3_INTEGER);

            try {
                $results = $stmt->execute();
            } catch (Exception $e) {
                echo 'Caught exception: ' . $e->getMessage();
                exit();
            }

            if ($results) {
                $row = $results->fetchArray(SQLITE3_ASSOC);
                if ($row) {
                    $first = $row["first_name"];
                    $last  = $row["last_name"];
                    echo "<pre>ID: {$id}<br />First name: {$first}<br />Surname: {$last}</pre>";
                } else {
                    echo "<pre>No user found with ID: {$id}</pre>";
                }
                $results->finalize();
            } else {
                echo "<pre>Error in fetch: " . $sqlite_db_connection->lastErrorMsg() . "</pre>";
            }
            break;
    }
}

?>
