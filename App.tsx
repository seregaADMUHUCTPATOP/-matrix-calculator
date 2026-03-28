import React, { useState } from 'react';

interface Matrix {
  rows: number;
  cols: number;
  data: number[][];
}

const MatrixComponent = () => {
  const [matrixA, setMatrixA] = useState<Matrix>({ rows: 2, cols: 2, data: [[1, 2], [3, 4]] });
  const [matrixB, setMatrixB] = useState<Matrix>({ rows: 2, cols: 2, data: [[5, 6], [7, 8]] });
  const [result, setResult] = useState<Matrix | null>(null);
  const [matrixARows, setMatrixARows] = useState<number>(2);
  const [matrixACols, setMatrixACols] = useState<number>(2);
  const [matrixBRows, setMatrixBRows] = useState<number>(2);
  const [matrixBCols, setMatrixBCols] = useState<number>(2);

  const handleMatrixChange = (matrix: Matrix, setMatrix: (matrix: Matrix) => void, row: number, col: number, value: number) => {
    const newData = [...matrix.data];
    newData[row][col] = value;
    setMatrix({ ...matrix, data: newData });
  };

  const handleAdd = () => {
    if (matrixA.rows !== matrixB.rows || matrixA.cols !== matrixB.cols) {
      alert('Матрицы должны иметь одинаковую размерность');
      return;
    }
    const newData = matrixA.data.map((row, i) => row.map((_, j) => matrixA.data[i][j] + matrixB.data[i][j]));
    setResult({ rows: matrixA.rows, cols: matrixA.cols, data: newData });
  };

  const handleSubtract = () => {
    if (matrixA.rows !== matrixB.rows || matrixA.cols !== matrixB.cols) {
      alert('Матрицы должны иметь одинаковую размерность');
      return;
    }
    const newData = matrixA.data.map((row, i) => row.map((_, j) => matrixA.data[i][j] - matrixB.data[i][j]));
    setResult({ rows: matrixA.rows, cols: matrixA.cols, data: newData });
  };

  const handleMultiply = () => {
    if (matrixA.cols !== matrixB.rows) {
      alert('Количество столбцов первой матрицы должно быть равно количеству строк второй матрицы');
      return;
    }
    const newData = matrixA.data.map((rowA) => matrixB.data[0].map((_, colIndex) => rowA.reduce((acc, val, rowIndex) => acc + val * matrixB.data[rowIndex][colIndex], 0)));
    setResult({ rows: matrixA.rows, cols: matrixB.cols, data: newData });
  };

  const handleDeterminant = () => {
    if (matrixA.rows !== matrixA.cols) {
      alert('Матрица должна быть квадратной');
      return;
    }
    const determinant = calculateDeterminant(matrixA.data);
    alert(`Определитель матрицы: ${determinant}`);
  };

  const handleTranspose = () => {
    const newData = matrixA.data[0].map((_, colIndex) => matrixA.data.map(row => row[colIndex]));
    setResult({ rows: matrixA.cols, cols: matrixA.rows, data: newData });
  };

  const handleMatrixSizeChange = () => {
    const newDataA = Array(matrixARows).fill(0).map(() => Array(matrixACols).fill(0));
    const newDataB = Array(matrixBRows).fill(0).map(() => Array(matrixBCols).fill(0));
    setMatrixA({ rows: matrixARows, cols: matrixACols, data: newDataA });
    setMatrixB({ rows: matrixBRows, cols: matrixBCols, data: newDataB });
  };

  return (
    <div className="container mx-auto p-4 pt-6 mt-10">
      <h1 className="text-3xl font-bold mb-4">Матрицы</h1>
      <div className="flex flex-wrap justify-center mb-4">
        <div className="flex flex-col items-center mx-4">
          <h2 className="text-2xl font-bold mb-2">Матрица A</h2>
          <div className="flex mb-2">
            <input
              type="number"
              value={matrixARows}
              onChange={(e) => setMatrixARows(parseInt(e.target.value))}
              className="w-10 h-10 text-center border border-gray-400 rounded mx-1"
            />
            <input
              type="number"
              value={matrixACols}
              onChange={(e) => setMatrixACols(parseInt(e.target.value))}
              className="w-10 h-10 text-center border border-gray-400 rounded mx-1"
            />
          </div>
          {matrixA.data.map((row, i) => (
            <div key={i} className="flex mb-2">
              {row.map((val, j) => (
                <input
                  key={j}
                  type="number"
                  value={val}
                  onChange={(e) => handleMatrixChange(matrixA, setMatrixA, i, j, parseInt(e.target.value))}
                  className="w-10 h-10 text-center border border-gray-400 rounded mx-1"
                />
              ))}
            </div>
          ))}
        </div>
        <div className="flex flex-col items-center mx-4">
          <h2 className="text-2xl font-bold mb-2">Матрица B</h2>
          <div className="flex mb-2">
            <input
              type="number"
              value={matrixBRows}
              onChange={(e) => setMatrixBRows(parseInt(e.target.value))}
              className="w-10 h-10 text-center border border-gray-400 rounded mx-1"
            />
            <input
              type="number"
              value={matrixBCols}
              onChange={(e) => setMatrixBCols(parseInt(e.target.value))}
              className="w-10 h-10 text-center border border-gray-400 rounded mx-1"
            />
          </div>
          {matrixB.data.map((row, i) => (
            <div key={i} className="flex mb-2">
              {row.map((val, j) => (
                <input
                  key={j}
                  type="number"
                  value={val}
                  onChange={(e) => handleMatrixChange(matrixB, setMatrixB, i, j, parseInt(e.target.value))}
                  className="w-10 h-10 text-center border border-gray-400 rounded mx-1"
                />
              ))}
            </div>
          ))}
        </div>
      </div>
      <div className="flex flex-wrap justify-center mb-4">
        <button className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded" onClick={handleMatrixSizeChange}>Применить размер</button>
        <button className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded" onClick={handleAdd}>Сложение</button>
        <button className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded" onClick={handleSubtract}>Вычитание</button>
        <button className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded" onClick={handleMultiply}>Умножение</button>
        <button className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded" onClick={handleDeterminant}>Определитель</button>
        <button className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded" onClick={handleTranspose}>Транспонирование</button>
      </div>
      {result && (
        <div className="flex flex-wrap justify-center mb-4">
          <div className="flex flex-col items-center mx-4">
            <h2 className="text-2xl font-bold mb-2">Результат</h2>
            {result.data.map((row, i) => (
              <div key={i} className="flex mb-2">
                {row.map((val, j) => (
                  <div key={j} className="w-10 h-10 text-center border border-gray-400 rounded mx-1">{val}</div>
                ))}
              </div>
            ))}
          </div>
        </div>
      )}
    </div>
  );
};

const calculateDeterminant = (matrix: number[][]) => {

  return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
};

export default MatrixComponent;
