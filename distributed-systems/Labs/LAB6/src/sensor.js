// Aplicação 1: monitora (simula) a temperatura e publica no broker
const mqtt = require('mqtt')

const BROKER_URL = 'mqtt://localhost:1883'
const TOPIC_TEMP = 'casa/sala/temperatura'
const INTERVALO_MS = 2000

const client = mqtt.connect(BROKER_URL, {
  clientId: `sensor_${Math.random().toString(16).slice(3)}`,
  clean: true,
  reconnectPeriod: 2000,
})

let temperatura = 25 // valor inicial

client.on('connect', () => {
  console.log(`[SENSOR] Conectado em ${BROKER_URL}`)

  setInterval(() => {
    // variação aleatória entre -1.5 e +1.5 °C, mantendo entre 15 e 40
    const variacao = (Math.random() - 0.5) * 3
    temperatura = Math.min(40, Math.max(15, temperatura + variacao))

    const payload = JSON.stringify({
      temperatura: Number(temperatura.toFixed(1)),
      unidade: 'C',
      timestamp: new Date().toISOString(),
    })

    client.publish(TOPIC_TEMP, payload, { qos: 1, retain: true }, (err) => {
      if (err) return console.error('[SENSOR] Erro ao publicar:', err)
      console.log(`[SENSOR] Publicado em ${TOPIC_TEMP}: ${payload}`)
    })
  }, INTERVALO_MS)
})

client.on('error', (err) => console.error('[SENSOR] Erro:', err.message))
client.on('reconnect', () => console.log('[SENSOR] Reconectando...'))