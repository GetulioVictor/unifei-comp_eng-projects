#!/usr/bin/env bash
# Controle do WAF: ./waf.sh on | off | detect | status | paranoia <1-4>
set -o pipefail
cd "$(dirname "$0")"

definir() {  # definir CHAVE VALOR
  sed -i.bak "s/^$1=.*/$1=$2/" .env && rm -f .env.bak
}

aplicar() {
  docker compose up -d waf
  echo "Aguardando o WAF reiniciar..."
  sleep 4
  ./waf.sh status
}

case "$1" in
  on)     definir WAF_MODE On;            aplicar ;;
  off)    definir WAF_MODE Off;           aplicar ;;
  detect) definir WAF_MODE DetectionOnly; aplicar ;;
  paranoia)
    [[ "$2" =~ ^[1-4]$ ]] || { echo "Uso: ./waf.sh paranoia <1-4>"; exit 1; }
    definir WAF_PARANOIA "$2"; aplicar ;;
  status)
    echo "Configuracao no .env:"
    grep -E '^WAF_' .env | sed 's/^/  /'
    echo "Em execucao no container:"
    docker exec waf printenv MODSEC_RULE_ENGINE BLOCKING_PARANOIA ANOMALY_INBOUND 2>/dev/null \
      | sed 's/^/  /' || echo "  container waf nao esta rodando"
    ;;
  *)
    echo "Uso: ./waf.sh on | off | detect | status | paranoia <1-4>"
    echo "  on        bloqueia ataques"
    echo "  detect    apenas registra no log, nao bloqueia"
    echo "  off       desliga o ModSecurity"
    echo "  paranoia  muda o nivel de rigor do OWASP CRS"
    exit 1 ;;
esac