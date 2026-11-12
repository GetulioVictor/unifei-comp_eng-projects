// Aplicação 2: assina a temperatura e age conforme o valor e a variação
const mqtt = require('mqtt')

const BROKER_URL = 'mqtt://localhost:1883'
const TOPIC_TEMP = 'casa/sala/temperatura'
const TOPIC_AR = 'casa/sala/ar-condicionado/comando'
const TOPIC_ALERTA = 'casa/sala/alerta'

const LIMITE_LIGAR = 28    // °C: acima disso liga o ar
const LIMITE_DESLIGAR = 24 // °C: abaixo disso desliga o ar (histerese evita liga/desliga constante)
const VARIACAO_BRUSCA = 1.2 // °C entre duas leituras consecutivas

const client = mqtt.connect(BROKER_URL, {
  clientId: `atuador_${Math.random().toString(16).slice(3)}`,
  clean: true,
  reconnectPeriod: 2000,
})

let temperaturaAnterior = null
let arLigado = false

function enviarComando(comando) {
  client.publish(TOPIC_AR, comando, { qos: 1, retain: true }, (err) => {
    if (err) console.error('[ATUADOR] Erro ao enviar comando:', err)
  })
}

client.on('connect', () => {
  console.log(`[ATUADOR] Conectado em ${BROKER_URL}`)
  client.subscribe(TOPIC_TEMP, { qos: 1 }, (err) => {
    if (err) return console.error('[ATUADOR] Erro ao assinar:', err)
    console.log(`[ATUADOR] Assinado em '${TOPIC_TEMP}'`)
  })
})

client.on('message', (topic, payload) => {
  let dados
  try {
    dados = JSON.parse(payload.toString())
  } catch {
    return console.error('[ATUADOR] Mensagem inválida:', payload.toString())
  }

  const temp = dados.temperatura
  const delta = temperaturaAnterior === null ? 0 : temp - temperaturaAnterior
  const sinal = delta > 0 ? '+' : ''
  console.log(`[ATUADOR] Temp: ${temp}°C (variação ${sinal}${delta.toFixed(1)}°C) | Ar: ${arLigado ? 'LIGADO' : 'DESLIGADO'}`)

  // Reação à temperatura
  if (temp >= LIMITE_LIGAR && !arLigado) {
    arLigado = true
    console.log('[ATUADOR] Muito quente → LIGANDO ar-condicionado')
    enviarComando('ON')
  } else if (temp <= LIMITE_DESLIGAR && arLigado) {
    arLigado = false
    console.log('[ATUADOR]  Temperatura agradável → DESLIGANDO ar-condicionado')
    enviarComando('OFF')
  }

  // Reação à variação brusca
  if (Math.abs(delta) >= VARIACAO_BRUSCA) {
    const msg = JSON.stringify({
      tipo: delta > 0 ? 'SUBIDA_BRUSCA' : 'QUEDA_BRUSCA',
      variacao: Number(delta.toFixed(1)),
      temperatura: temp,
      timestamp: new Date().toISOString(),
    })
    console.log(`[ATUADOR]  Variação brusca: ${msg}`)
    client.publish(TOPIC_ALERTA, msg, { qos: 1 })
  }

  temperaturaAnterior = temp
})

client.on('error', (err) => console.error('[ATUADOR] Erro:', err.message))
client.on('reconnect', () => console.log('[ATUADOR] Reconectando...'))