const axios = require('axios').default;

const operacao = process.argv[2] || 'somar';
const valor1 = process.argv[3] || 10;
const valor2 = process.argv[4] || 5;

axios.get('http://localhost:3000/' + operacao + '/' + valor1 + '/' + valor2)
  .then(function (response) {
    console.log(response.data);
  })
  .catch(function (error) {
    if (error.response) {
      console.log(error.response.data);
    } else {
      console.log(error.message);
    }
  })
