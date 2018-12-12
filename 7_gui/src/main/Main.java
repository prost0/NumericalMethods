package main;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;
import java.io.IOException;

public class Main extends Application {
	@Override
	public void start(Stage stage) throws IOException {
		FXMLLoader loader = new FXMLLoader(getClass().getResource("/resources/main.fxml"));
		BorderPane root = loader.load();
		Scene scene = new Scene(root);

		scene.getStylesheets().add(getClass().getResource("/resources/styles/chart.css").toExternalForm());

		stage.setTitle("Numeric methods 7 Yakimovich");
		stage.setScene(scene);
		stage.show();
		stage.setResizable(false);
	}

	public static void main(String[] args) {
		launch(args);
	}
}
