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
import javafx.scene.chart.XYChart;
import javafx.scene.control.*;

import libnm.math.Matrix;
import libnm.math.Vector;
import libnm.math.expression.ExpTree;
import libnm.math.pde.Parabolic;
import libnm.util.Logger;
import libnm.util.Reader;

public class MainController implements Initializable {
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		method = new Parabolic();
		matU = new Matrix();
		vecX = new Vector();
		vecT = new Vector();

		scrollBarK.valueProperty().addListener(new ChangeListener<Number>() {
			@Override
			public void changed(ObservableValue<? extends Number> observable, Number oldValue, Number newValue) {
				int k = newValue.intValue();

				labelK.setText("Параметры графика (k = " + k + ")");

				updatePlotters(k);
			}
		});

		if (new File("input.txt").exists()) {
			Reader reader = new Reader("input.txt");

			fieldA.setText(reader.readLine());
			fieldB.setText(reader.readLine());
			fieldC.setText(reader.readLine());
			fieldExprF.setText(reader.readLine());
			fieldExprPsi.setText(reader.readLine());
			fieldAlpha.setText(reader.readLine());
			fieldBeta.setText(reader.readLine());
			fieldGamma.setText(reader.readLine());
			fieldDelta.setText(reader.readLine());
			fieldExprFi0.setText(reader.readLine());
			fieldExprFi1.setText(reader.readLine());
			fieldL.setText(reader.readLine());
			fieldK.setText(reader.readLine());
			fieldTau.setText(reader.readLine());
			fieldN.setText(reader.readLine());
			fieldExprU.setText(reader.readLine());

			reader.close();
		}
	}

	public void buttonSolve(ActionEvent actionEvent) {
		int scheme;
		int boundCond;
		Logger output = new Logger("output.txt");
		RadioButton rbScheme = (RadioButton)rbGroupScheme.getSelectedToggle();
		RadioButton rbBoundCond = (RadioButton)rbGroupBoundCond.getSelectedToggle();

		//scheme = Parabolic.SCHEME_IMPLICIT;

		if (rbScheme == radioButtonExplicit) {
			scheme = Parabolic.SCHEME_EXPLICIT;
		} else if (rbScheme == radioButtonImplicit) {
			scheme = Parabolic.SCHEME_IMPLICIT;
		} else {
			scheme = Parabolic.SCHEME_CRANK_NICOLSON;
		}

		//boundCond = Parabolic.BOUNDARY_CONDITION_2_1;

		if (rbBoundCond == radioButtonBoundCond21) {
			boundCond = Parabolic.BOUNDARY_CONDITION_2_1;
		} else if (rbBoundCond == radioButtonBoundCond32) {
			boundCond = Parabolic.BOUNDARY_CONDITION_3_2;
		} else {
			boundCond = Parabolic.BOUNDARY_CONDITION_2_2;
		}


//		method.setExprPsi(new ExpTree(fieldExprPsi.getText()));
//		method.setAlpha(Double.parseDouble(fieldAlpha.getText()));
//		method.setBeta(Double.parseDouble(fieldBeta.getText()));
//		method.setGamma(Double.parseDouble(fieldGamma.getText()));
//		method.setDelta(Double.parseDouble(fieldDelta.getText()));
//		method.setExprFi0(new ExpTree(fieldExprFi0.getText()));
//		method.setExprFi1(new ExpTree(fieldExprFi1.getText()));
//		method.setL(Double.parseDouble(fieldL.getText()));

		method.setA(Double.parseDouble(fieldA.getText()));
		method.setB(Double.parseDouble("0"));
		method.setC(Double.parseDouble("0"));
		method.setExprF(new ExpTree("0"));
		method.setExprPsi(new ExpTree("sin(x)"));
		method.setAlpha(Double.parseDouble("1"));
		method.setBeta(Double.parseDouble("0"));
		method.setGamma(Double.parseDouble("1"));
		method.setDelta(Double.parseDouble("0"));
		method.setExprFi0(new ExpTree("e^(-1*a*t)"));
		method.setExprFi1(new ExpTree("-e^(-1*a*t)"));
		method.setL(Double.parseDouble("3.141592653589793"));
		method.setK(Integer.parseInt(fieldK.getText()));
		method.setTau(Double.parseDouble(fieldTau.getText()));
		method.setN(Integer.parseInt(fieldN.getText()));
		method.setExprU(new ExpTree("e^(-a*t)*sin(x)"));

		sigma.setText( Double.toString(Math.pow(Double.parseDouble(fieldA.getText()), 2) * Double.parseDouble(fieldTau.getText()) / Math.pow((3.141592653589793 / Integer.parseInt(fieldN.getText())), 2)));

		method.solve(scheme, boundCond, matU, vecX, vecT);

		output.writeln(matU.toString());
		output.close();

		scrollBarK.setMax(Double.parseDouble(fieldK.getText()));

		initPlotters();
		updatePlotters(0);
	}

	private void initPlotters() {
		seriesAnalytical = new XYChart.Series<>();
		seriesNumerical = new XYChart.Series<>();
		seriesError = new XYChart.Series<>();
		seriesAnalytical.setName("Анал.");
		seriesNumerical.setName("Числ.");
		seriesError.setName("e(t)");

		for (int j = 0; j < vecX.getSize(); ++j) {
			seriesAnalytical.getData().add(new XYChart.Data<>(0.0, 0.0));
			seriesNumerical.getData().add(new XYChart.Data<>(0.0, 0.0));
		}

		for (int i = 0; i < matU.getM(); ++i) {
			double error = 0.0;

			for (int j = 0; j < matU.getN(); ++j) {
				error = Math.max(error, Math.abs(matU.get(i, j) - method.u(vecX.get(j), vecT.get(i))));
			}

			seriesError.getData().add(new XYChart.Data<>(vecT.get(i), error));
		}

		plotterSolution.setCreateSymbols(false);
		plotterSolution.getData().clear();
		plotterSolution.getData().add(seriesAnalytical);
		plotterSolution.getData().add(seriesNumerical);

		plotterError.setCreateSymbols(false);
		plotterError.getData().clear();
		plotterError.getData().add(seriesError);
	}

	private void updatePlotters(int k) {
		for (int j = 0; j < vecX.getSize(); ++j) {
			seriesAnalytical.getData().set(j, new XYChart.Data<>(vecX.get(j), method.u(vecX.get(j), vecT.get(k))));
			seriesNumerical.getData().set(j, new XYChart.Data<>(vecX.get(j), matU.get(k, j)));
		}
	}

	private Parabolic method;
	private Matrix matU;
	private Vector vecX;
	private Vector vecT;
	private XYChart.Series<Double, Double> seriesAnalytical;
	private XYChart.Series<Double, Double> seriesNumerical;
	private XYChart.Series<Double, Double> seriesError;

	@FXML
	private LineChart<Double, Double> plotterSolution;
	@FXML
	private LineChart<Double, Double> plotterError;
	@FXML
	private TextField fieldA;
	@FXML
	private TextField fieldB;
	@FXML
	private TextField fieldC;
	@FXML
	private TextField fieldExprF;
	@FXML
	private TextField fieldAlpha;
	@FXML
	private TextField fieldBeta;
	@FXML
	private TextField fieldGamma;
	@FXML
	private TextField fieldDelta;
	@FXML
	private TextField fieldExprFi0;
	@FXML
	private TextField fieldExprFi1;
	@FXML
	private TextField fieldL;
	@FXML
	private TextField fieldExprPsi;
	@FXML
	private TextField fieldK;
	@FXML
	private TextField fieldTau;
	@FXML
	private TextField sigma;
	@FXML
	private TextField fieldN;
	@FXML
	private TextField fieldExprU;
	@FXML
	private ToggleGroup rbGroupScheme;
	@FXML
	private ToggleGroup rbGroupBoundCond;
	@FXML
	private RadioButton radioButtonExplicit;
	@FXML
	private RadioButton radioButtonImplicit;
	@FXML
	private RadioButton radioButtonBoundCond21;
	@FXML
	private RadioButton radioButtonBoundCond32;
	@FXML
	private Label labelK;
	@FXML
	private ScrollBar scrollBarK;
}
