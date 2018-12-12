package main;

import java.io.File;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.Initializable;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.control.*;

import libnm.math.Matrix;
import libnm.math.Vector;
import libnm.math.expression.ExpTree;
import libnm.math.pde.Elliptic;
import libnm.util.Logger;
import libnm.util.Reader;

public class MainController implements Initializable, ChangeListener<Number> {
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		isX = true;
		method = new Elliptic();
		matU = new Matrix();
		vecX = new Vector();
		vecY = new Vector();

		scrollBarK.valueProperty().addListener(this);

		if (new File("input.txt").exists()) {
			Reader reader = new Reader("input.txt");

			fieldBx.setText(reader.readLine());
			fieldBy.setText(reader.readLine());
			fieldC.setText(reader.readLine());
			fieldExprF.setText(reader.readLine());
			fieldAlpha1.setText(reader.readLine());
			fieldBeta1.setText(reader.readLine());
			fieldAlpha2.setText(reader.readLine());
			fieldBeta2.setText(reader.readLine());
			fieldAlpha3.setText(reader.readLine());
			fieldBeta3.setText(reader.readLine());
			fieldAlpha4.setText(reader.readLine());
			fieldBeta4.setText(reader.readLine());
			fieldExprFi1.setText(reader.readLine());
			fieldExprFi2.setText(reader.readLine());
			fieldExprFi3.setText(reader.readLine());
			fieldExprFi4.setText(reader.readLine());
			fieldLx.setText(reader.readLine());
			fieldLy.setText(reader.readLine());
			fieldNx.setText(reader.readLine());
			fieldNy.setText(reader.readLine());
			fieldOmega.setText(reader.readLine());
			fieldEps.setText(reader.readLine());
			fieldExprU.setText(reader.readLine());

			reader.close();
		}
	}

	@Override
	public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
		updatePlotters();
	}

	public void buttonSolve(ActionEvent actionEvent) {
		int methodType;
		Logger output = new Logger("output.txt");
		RadioButton rbMethod = (RadioButton)rbGroupMethod.getSelectedToggle();

		if (rbMethod == radioButtonLiebmann) {
			methodType = Elliptic.METHOD_LIEBMANN;
		} else {
			methodType = Elliptic.METHOD_SEIDEL;
		}
		method.setBx(Double.parseDouble("1"));
		method.setBy(Double.parseDouble("1"));
		method.setC(Double.parseDouble("0"));
		method.setExprF(new ExpTree("0"));
//		method.setBx(Double.parseDouble(fieldBx.getText()));
//		method.setBy(Double.parseDouble(fieldBy.getText()));
//		method.setC(Double.parseDouble(fieldC.getText()));
//		method.setExprF(new ExpTree(fieldExprF.getText()));
		method.setAlpha1(Double.parseDouble("0"));
		method.setBeta1(Double.parseDouble("1"));
		method.setAlpha2(Double.parseDouble("0"));
		method.setBeta2(Double.parseDouble("1"));
		method.setAlpha3(Double.parseDouble("0"));
		method.setBeta3(Double.parseDouble("1"));
		method.setAlpha4(Double.parseDouble("0"));
		method.setBeta4(Double.parseDouble("1"));
		method.setExprFi1(new ExpTree("y"));
		method.setExprFi2(new ExpTree("1+y"));
		method.setExprFi3(new ExpTree("x"));
		method.setExprFi4(new ExpTree("1+x"));
//		method.setAlpha1(Double.parseDouble(fieldAlpha1.getText()));
//		method.setBeta1(Double.parseDouble(fieldBeta1.getText()));
//		method.setAlpha2(Double.parseDouble(fieldAlpha2.getText()));
//		method.setBeta2(Double.parseDouble(fieldBeta2.getText()));
//		method.setAlpha3(Double.parseDouble(fieldAlpha3.getText()));
//		method.setBeta3(Double.parseDouble(fieldBeta3.getText()));
//		method.setAlpha4(Double.parseDouble(fieldAlpha4.getText()));
//		method.setBeta4(Double.parseDouble(fieldBeta4.getText()));
//		method.setExprFi1(new ExpTree(fieldExprFi1.getText()));
//		method.setExprFi2(new ExpTree(fieldExprFi2.getText()));
//		method.setExprFi3(new ExpTree(fieldExprFi3.getText()));
//		method.setExprFi4(new ExpTree(fieldExprFi4.getText()));
		method.setLx(Double.parseDouble("1"));
		method.setLy(Double.parseDouble("1"));
		method.setNx(Integer.parseInt(fieldNx.getText()));
		method.setNy(Integer.parseInt(fieldNy.getText()));
		method.setOmega(Double.parseDouble(fieldOmega.getText()));
		method.setEps(Double.parseDouble(fieldEps.getText()));
		method.setExprU(new ExpTree("x+y"));

		int iterations = method.solve(methodType, matU, vecX, vecY);

		output.writeln("Iterations: " + iterations);
		output.writeln(matU.toString());
		output.close();

		rbSliceClick(null);
		updatePlotters();
	}

	public void rbSliceClick(ActionEvent actionEvent) {
		RadioButton rbSlice = (RadioButton)rbGroupSlice.getSelectedToggle();

		if (rbSlice == radioButtonSliceX) {
			scrollBarK.setMax(Double.parseDouble(fieldNx.getText()));
			plotterSolutionAxisX.setLabel("y");
			plotterErrorAxisX.setLabel("y");
			isX = true;
		} else {
			scrollBarK.setMax(Double.parseDouble(fieldNy.getText()));
			plotterSolutionAxisX.setLabel("x");
			plotterErrorAxisX.setLabel("x");
			isX = false;
		}

		initPlotters();

		scrollBarK.setValue(0.0);

		updatePlotters();
	}

	private void initPlotters() {
		seriesAnalytical = new XYChart.Series<>();
		seriesNumerical = new XYChart.Series<>();
		seriesError = new XYChart.Series<>();
		seriesAnalytical.setName("Анал.");
		seriesNumerical.setName("Числ.");
		seriesError.setName("e" + (isX ? "(y)" : "(x)"));

		for (int j = 0; j < (isX ? vecY.getSize() : vecX.getSize()); ++j) {
			seriesAnalytical.getData().add(new XYChart.Data<>(0.0, 0.0));
			seriesNumerical.getData().add(new XYChart.Data<>(0.0, 0.0));
		}

		if (isX) {
			for (int i = 0; i < matU.getM(); ++i) {
				double error = 0.0;

				for (int j = 0; j < matU.getN(); ++j) {
					error = Math.max(error, Math.abs(matU.get(i, j) - method.u(vecX.get(j), vecY.get(i))));
				}

				seriesError.getData().add(new XYChart.Data<>(vecY.get(i), error));
			}
		} else {
			for (int j = 0; j < matU.getN(); ++j) {
				double error = 0.0;

				for (int i = 0; i < matU.getM(); ++i) {
					error = Math.max(error, Math.abs(matU.get(i, j) - method.u(vecX.get(j), vecY.get(i))));
				}

				seriesError.getData().add(new XYChart.Data<>(vecX.get(j), error));
			}
		}

		plotterSolution.setCreateSymbols(false);
		plotterSolution.getData().clear();
		plotterSolution.getData().add(seriesAnalytical);
		plotterSolution.getData().add(seriesNumerical);

		plotterError.setCreateSymbols(false);
		plotterError.getData().clear();
		plotterError.getData().add(seriesError);
	}

	private void updatePlotters() {
		int k = (int)scrollBarK.getValue();

		labelK.setText("Параметры графика (k = " + k + ")");

		if (isX) {
			for (int i = 0; i < vecY.getSize(); ++i) {
				seriesAnalytical.getData().set(i, new XYChart.Data<>(vecY.get(i), method.u(vecX.get(k), vecY.get(i))));
				seriesNumerical.getData().set(i, new XYChart.Data<>(vecY.get(i), matU.get(i, k)));
			}
		} else {
			for (int j = 0; j < vecX.getSize(); ++j) {
				seriesAnalytical.getData().set(j, new XYChart.Data<>(vecX.get(j), method.u(vecX.get(j), vecY.get(k))));
				seriesNumerical.getData().set(j, new XYChart.Data<>(vecX.get(j), matU.get(k, j)));
			}
		}
	}

	private boolean isX;
	private Elliptic method;
	private Matrix matU;
	private Vector vecX;
	private Vector vecY;
	private XYChart.Series<Double, Double> seriesAnalytical;
	private XYChart.Series<Double, Double> seriesNumerical;
	private XYChart.Series<Double, Double> seriesError;

	@FXML
	private LineChart<Double, Double> plotterSolution;
	@FXML
	private LineChart<Double, Double> plotterError;
	@FXML
	private NumberAxis plotterSolutionAxisX;
	@FXML
	private NumberAxis plotterErrorAxisX;
	@FXML
	private TextField fieldBx;
	@FXML
	private TextField fieldBy;
	@FXML
	private TextField fieldC;
	@FXML
	private TextField fieldExprF;
	@FXML
	private TextField fieldAlpha1;
	@FXML
	private TextField fieldBeta1;
	@FXML
	private TextField fieldAlpha2;
	@FXML
	private TextField fieldBeta2;
	@FXML
	private TextField fieldAlpha3;
	@FXML
	private TextField fieldBeta3;
	@FXML
	private TextField fieldAlpha4;
	@FXML
	private TextField fieldBeta4;
	@FXML
	private TextField fieldExprFi1;
	@FXML
	private TextField fieldExprFi2;
	@FXML
	private TextField fieldExprFi3;
	@FXML
	private TextField fieldExprFi4;
	@FXML
	private TextField fieldLx;
	@FXML
	private TextField fieldLy;
	@FXML
	private TextField fieldOmega;
	@FXML
	private TextField fieldEps;
	@FXML
	private TextField fieldNx;
	@FXML
	private TextField fieldNy;
	@FXML
	private TextField fieldExprU;
	@FXML
	private ToggleGroup rbGroupMethod;
	@FXML
	private ToggleGroup rbGroupSlice;
	@FXML
	private RadioButton radioButtonLiebmann;
	@FXML
	private RadioButton radioButtonSliceX;
	@FXML
	private Label labelK;
	@FXML
	private ScrollBar scrollBarK;
}
