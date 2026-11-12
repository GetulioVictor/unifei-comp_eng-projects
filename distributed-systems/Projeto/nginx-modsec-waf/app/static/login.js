const EXEMPLOS = {
  valido: { u: 'root', p: 'root' },
  errado: { u: 'root', p: 'senha-errada' },
  sqli:   { u: "' OR 1=1 --", p: 'qualquer' },
  xss:    { u: '<img src=x onerror="alert(`XSS executado`)">', p: 'qualquer' },
};

const $ = (id) => document.getElementById(id);

function mostrar(tipo, titulo, detalhe = '') {
  const caixa = $('mensagem');
  caixa.className = `mensagem ${tipo}`;
  caixa.replaceChildren();
  const t = document.createElement('strong');
  t.textContent = titulo;
  caixa.append(t);
  if (detalhe) {
    const d = document.createElement('span');
    d.textContent = detalhe;
    caixa.append(d);
  }
}

// VULNERAVEL DE PROPOSITO (XSS refletido): o usuario digitado e inserido como HTML.
// createContextualFragment executa inclusive tags <script>.
function mostrarErroLogin(titulo, usuario, detalhe = '') {
  const caixa = $('mensagem');
  caixa.className = 'mensagem erro';
  let html = `<strong>${titulo}</strong><span>Usuário informado: ${usuario}</span>`;
  if (detalhe) html += `<span>Erro do banco: ${detalhe}</span>`;
  caixa.replaceChildren(document.createRange().createContextualFragment(html));
}

async function enviarLogin(evento) {
  evento.preventDefault();
  const corpo = new URLSearchParams(new FormData(evento.target));

  let resposta;
  try {
    resposta = await fetch('/api/login', { method: 'POST', body: corpo, credentials: 'same-origin' });
  } catch {
    mostrar('erro', 'Falha de conexão com o servidor.');
    return;
  }
  const dados = await resposta.json().catch(() => ({}));

  if (resposta.ok && dados.ok) {
    window.location.href = dados.redirecionar || '/painel';
  } else if (resposta.status === 403 || resposta.status === 405 || resposta.status === 415) {
    // A aplicacao nunca devolve esses codigos: eles so vem do WAF
    mostrar('bloqueado', 'Requisição bloqueada pelo WAF.',
      'Foi detectado conteúdo malicioso na requisição. O evento foi registrado no log de auditoria.');
  } else if (resposta.status === 401) {
    mostrarErroLogin('Usuário ou senha inválidos.', dados.usuario ?? '');
  } else if (resposta.status === 429) {
    mostrar('aviso', 'Muitas tentativas de login.', 'Proteção contra força bruta ativada. Aguarde alguns segundos.');
  } else if (resposta.status === 500) {
    mostrarErroLogin('Erro interno no servidor.', dados.usuario ?? '', dados.detalhe ?? '');
  } else {
    mostrar('erro', `Resposta inesperada (HTTP ${resposta.status}).`);
  }
}

document.addEventListener('DOMContentLoaded', () => {
  $('form-login').addEventListener('submit', enviarLogin);
  document.querySelectorAll('[data-exemplo]').forEach((botao) => {
    botao.addEventListener('click', () => {
      const ex = EXEMPLOS[botao.dataset.exemplo];
      $('username').value = ex.u;
      $('password').value = ex.p;
      $('mensagem').className = 'mensagem oculto';
    });
  });
});