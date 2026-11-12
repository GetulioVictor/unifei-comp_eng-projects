document.addEventListener('DOMContentLoaded', async () => {
  const resposta = await fetch('/api/me', { credentials: 'same-origin' }).catch(() => null);
  const dados = resposta ? await resposta.json().catch(() => ({})) : {};

  if (!resposta || !resposta.ok || !dados.ok) {
    window.location.href = '/';
    return;
  }
  document.getElementById('usuario').textContent = dados.usuario;
  document.getElementById('replica').textContent = dados.instancia;

  document.getElementById('btn-sair').addEventListener('click', async () => {
    await fetch('/api/logout', { method: 'POST', credentials: 'same-origin' }).catch(() => null);
    window.location.href = '/';
  });
});
