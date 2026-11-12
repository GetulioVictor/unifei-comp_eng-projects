const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  res.send('Calculadora REST: /somar, /subtrair, /multiplicar, /dividir')
})

app.get('/somar/:valor1/:valor2', (req, res) => {
  const resultado = Number(req.params.valor1) + Number(req.params.valor2)
  res.send('Resultado: ' + resultado)
})

app.get('/subtrair/:valor1/:valor2', (req, res) => {
  const resultado = Number(req.params.valor1) - Number(req.params.valor2)
  res.send('Resultado: ' + resultado)
})

app.get('/multiplicar/:valor1/:valor2', (req, res) => {
  const resultado = Number(req.params.valor1) * Number(req.params.valor2)
  res.send('Resultado: ' + resultado)
})

app.get('/dividir/:valor1/:valor2', (req, res) => {
  if (Number(req.params.valor2) === 0) {
    res.status(400).send('Erro: divisao por zero')
    return
  }
  const resultado = Number(req.params.valor1) / Number(req.params.valor2)
  res.send('Resultado: ' + resultado)
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})
